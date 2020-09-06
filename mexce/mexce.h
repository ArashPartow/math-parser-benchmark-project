//
// Mini Expression Compiler/Evaluator
// ==================================
//
// mexce.h
// Author: Ioannis Makris
//
// mexce can compile and evaluate a mathematical expression at runtime.
// The generated machine code will mostly use the FPU.
//
// An example:
// -----------
//
// float   x  = 0.0f;
// double  y  = 0.1;
// int     z  = 200;
// 
// mexce::evaluator eval;
// 
// eval.bind(x, "x");
// eval.bind(y, "y");
// eval.bind(z, "z");
// 
// eval.assign_expression("0.3+(-sin(2.33+x-logb((.3*pi+(88/y)/e),3.2+z)))/98");
// 
// cout << endl << "Evaluation results:" << endl;
// for (int i = 0; i < 10; i++, x-=0.1f, y+=0.212, z+=2) {
//     cout << "  " << eval.evaluate() << endl; // evaluation will use bound variables x, y and z
// }
//

#ifndef MEXCE_INCLUDED
#define MEXCE_INCLUDED

#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstring>
#include <deque>
#include <exception>
#include <iomanip>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>


#if defined(_M_X64) || defined(__x86_64__)
    #define MEXCE_64
#elif defined(_M_IX86) || defined(__i386__)
    #define MEXCE_32
#else
    #error Unknown CPU architecture
#endif

#ifdef _WIN32
    #include <Windows.h>
#elif defined(__linux__)
    //#include <unistd.h>
    #include <sys/mman.h>
#endif



namespace mexce {


class evaluator;


namespace impl {

    struct Element;
    struct Value;
    struct Constant;
    struct Variable;
    struct Function;
    struct mexce_charstream;

    using std::abs;
    using std::deque;
    using std::exception;
    using std::get;
    using std::list;
    using std::logic_error;
    using std::make_pair;
    using std::make_shared;
    using std::make_tuple;
    using std::map;
    using std::next;
    using std::pair;
    using std::shared_ptr;
    using std::static_pointer_cast;
    using std::string;
    using std::stringstream;
    using std::vector;

    using constant_map_t    = map<string, shared_ptr<Constant> >;
    using variable_map_t    = map<string, shared_ptr<Variable> >;
    using elist_t           = list<shared_ptr<Element> >;
    using elist_it_t        = elist_t::iterator;
    using elist_const_it_t  = elist_t::const_iterator;

    std::shared_ptr<Constant> make_intermediate_constant(evaluator* ev, double v);
    uint8_t* push_intermediate_code(evaluator* ev, const std::string& s);
}



class evaluator
{
public:

    evaluator();
    ~evaluator();

    template <typename T>
    void bind(T& v, const std::string& s);

    void unbind(const std::string&);
    void assign_expression(std::string);
    double evaluate();

private:

    bool                    is_constant_expression      = false;
    double                  constant_expression_value   = 0.0;
    size_t                  m_buffer_size               = 0;
    std::string             m_expression;
    impl::elist_t           m_elist;
    std::list<std::string>  m_intermediate_code;
    impl::constant_map_t    m_intermediate_constants;  // produced during expression simplification
    impl::variable_map_t    m_variables;
    impl::constant_map_t    m_constants;

    double                (*evaluate_fptr)();

#ifdef MEXCE_64
    volatile double         m_x64_return_var;
#endif

    void compile_and_finalize_elist(impl::elist_it_t first, impl::elist_it_t last);

    friend
    std::shared_ptr<impl::Constant> impl::make_intermediate_constant(evaluator* ev, double v);

    friend
    uint8_t* impl::push_intermediate_code(evaluator* ev, const std::string& s);
};



class mexce_parsing_exception: public std::exception
{
public:
    explicit mexce_parsing_exception(const std::string& message, size_t position):
        m_message(message),
        m_position(position)
    {}

    virtual ~mexce_parsing_exception()  { }
    virtual const char* what() const throw() { return m_message.c_str(); }

protected:
    std::string             m_message;
    size_t                  m_position;
};



namespace impl {


#ifdef _WIN32
inline
size_t get_page_size()
{
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    return system_info.dwPageSize;
}
#endif


inline
uint8_t* get_executable_buffer(size_t sz)
{
#ifdef _WIN32
    static auto const page_size = get_page_size();
    return (uint8_t*)VirtualAlloc(nullptr, page_size, MEM_COMMIT, PAGE_READWRITE);
#elif defined(__linux__)
    return (uint8_t*)mmap(0, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
}


inline
double (*lock_executable_buffer(uint8_t* buffer, size_t sz))()
{
#ifdef _WIN32
    DWORD dummy;
    VirtualProtect(buffer, sz, PAGE_EXECUTE_READ, &dummy);
#elif defined(__linux__)
    if (mprotect((void*) buffer, sz, PROT_EXEC) != 0) {
        buffer = 0;
    }
#endif
    return reinterpret_cast<double (*)()>(buffer);
}


inline
void free_executable_buffer(double (*buffer)(), size_t sz)
{
    if (!buffer) {
        return;
    }
#ifdef _WIN32
    VirtualFree( (void*) buffer, 0, MEM_RELEASE);
#elif defined(__linux__)
    munmap((void *) buffer, sz);
#endif
}


enum Numeric_data_type
{
    M16INT,
    M32INT,
    M64INT,
    M32FP,
    M64FP,
};


enum Element_type
{
    CCONST,
    CVAR,
    CFUNC
};


enum Token_type
{
    UNDEFINED_TOKEN_TYPE,
    NUMERIC_LITERAL,
    CONSTANT_NAME,
    VARIABLE_NAME,
    FUNCTION_NAME,
    INFIX_1,            // infix operator, with priority 1 ( '^', i.e. power )
    INFIX_2,            // infix operator, with priority 2 ( '*' and '/' )
    INFIX_3,            // infix operator, with priority 3 ( '+' and '-' )
    INFIX_4,            // infix operator, with priority 4 ( '<' )
    RIGHT_PARENTHESIS,
    LEFT_PARENTHESIS,
    COMMA,
    FUNCTION_RIGHT_PARENTHESIS,
    FUNCTION_LEFT_PARENTHESIS,
    UNARY
};



inline
string double_to_hex( double v )
{
    uint64_t* u64p = (uint64_t*)&v;

    stringstream stream;
    stream << "0x" 
        << std::setfill ('0') << std::setw(sizeof(*u64p)*2) 
        << std::hex << *u64p;
    return stream.str();
}



struct Element
{
    Element_type element_type;
    Element(Element_type ct): element_type(ct) {}
};


struct Value: public Element
{
    volatile void*          address;
    Numeric_data_type       numeric_data_type;
    string                  name;

    Value(volatile void *   address,
        Numeric_data_type   numeric_data_type,
        Element_type        element_type,
        string              name)
    :
        Element             ( element_type      ),
        address             ( address           ),
        numeric_data_type   ( numeric_data_type ),
        name                ( name              ) {}
};


struct Constant: public Value
{
    Constant(string num, string name):
        Value( (volatile void *) &internal_constant, M64FP, CCONST, name),
        internal_constant(atof(num.data()))
    {}

    Constant(double num):
        Value( (volatile void *) &internal_constant, M64FP, CCONST, double_to_hex(num)),
        internal_constant(num)
    {}

    Constant(const Constant& rhs):
        Value(rhs),
        internal_constant(rhs.internal_constant)
    {
        address = (void*)&internal_constant;
    }

    double get_data_as_double() const {
        switch (this->numeric_data_type) {
            case M16INT: return (double)*((int16_t*)address);
            case M32INT: return (double)*((int32_t*)address);
            case M64INT: return (double)*((int64_t*)address);
            case M32FP:  return (double)*((float*  )address);
            case M64FP:  return         *((double* )address);
            default: return 0.0;
        }
    }

private:
    const double   internal_constant;
};


struct Variable: public Value
{
    bool referenced;

    Variable(volatile void * addr, string name, Numeric_data_type numeric_data_type):
        Value(addr, numeric_data_type, CVAR, name), referenced(false)
    {}
};


struct Function: public Element
{
    using optimizer_t = void (*)(elist_it_t, evaluator*, elist_t*);

    size_t              stack_req;
    string              name;
    size_t              num_args;
    
    vector<elist_it_t>  args;
    elist_it_t          parent;
    size_t              parent_arg_index = ~0; // index in postfix order (inverted), i.e. arg1-arg0

    list<elist_t>       absorbed[2];

    string              code;
    optimizer_t         optimizer;

    bool                force_not_constant = false;

    Function(
        const string& name,
        size_t      num_args,
        size_t      sreq,
        size_t      size,
        uint8_t    *code_buffer,
        optimizer_t optimizer = 0)
    :
        Element   ( CFUNC                        ),
        stack_req ( sreq                         ),
        name      ( name                         ),
        num_args  ( num_args                     ),
        args      ( vector<elist_it_t>(num_args) ),
        code      ( (char*)code_buffer, size     ),
        optimizer ( optimizer                    ) {}
};


struct mexce_charstream { stringstream s; };

template<typename T>
mexce_charstream& operator << (mexce_charstream &s, T data) {
    s.s.write((char*)&data, sizeof(T));
    return s;
}

inline
mexce_charstream& operator < (mexce_charstream &s, int v) {
    char ch = (char)v;
    s.s.write(&ch, 1);
    return s;
}



inline
shared_ptr<mexce::impl::Constant> make_intermediate_constant(evaluator* ev, double v)
{
    auto sc = make_shared<impl::Constant>(v);
    auto it = ev->m_intermediate_constants.find(sc->name);
    if (it == ev->m_intermediate_constants.end()) {
        ev->m_intermediate_constants[sc->name] = sc;
    }
    else {
        sc = it->second; // releases the constant we just created
    }
    return sc;
}



inline
uint8_t* push_intermediate_code(evaluator* ev, const string& s)
{
    ev->m_intermediate_code.push_back(string());
    ev->m_intermediate_code.back() = s;
    return (uint8_t*)&ev->m_intermediate_code.back()[0];
}



inline
void link_arguments(elist_t& elist)
{
    vector<elist_it_t > evec;
    for (auto y = elist.begin(); y != elist.end(); y++) {
        if ((*y)->element_type == CFUNC) {
            auto f = static_pointer_cast<Function>(*y);
            f->parent = elist.end();
            for (size_t i = 0; i < f->num_args; i++) {
                f->args[i] = evec.back();

                if ((*f->args[i])->element_type == CFUNC) {
                    auto cf = static_pointer_cast<Function>(*f->args[i]);
                    cf->parent = y;
                    cf->parent_arg_index = i; // postfix order (inverted)
                }
                evec.pop_back();
            }
        }
        evec.push_back(y);
    }
}


inline
Token_type get_infix_rank(char infix_op)
{
    switch (infix_op) {
        case '<': return INFIX_4;
        case '+':
        case '-': return INFIX_3;
        case '*':
        case '/': return INFIX_2;
        case '^': return INFIX_1;
    }

    assert(false);
    return UNDEFINED_TOKEN_TYPE;
}


inline Function Sin()
{
    static uint8_t code[] = {
        0xd9, 0xfe                                  // fsin
    };
    return Function("sin", 1, 0, sizeof(code), code);
}


inline Function Cos()
{
    static uint8_t code[] = {
        0xd9, 0xff                                  // fcos
    };
    return Function("cos", 1, 0, sizeof(code), code);
}


inline Function Tan()
{
    static uint8_t code[] = {
        0xd9, 0xf2,                                 // fptan
        0xdd, 0xd8                                  // fstp        st(0)
    };
    return Function("tan", 1, 1, sizeof(code), code);
}


inline Function Abs()
{
    static uint8_t code[] = {
        0xd9, 0xe1                                  // fabs
    };
    return Function("abs", 1, 0, sizeof(code), code);
}


inline Function Sfc()
{
    static uint8_t code[] = {
        0xd9, 0xf4,                                 // fxtract
        0xdd, 0xd9                                  // fstp        st(1)
    };
    return Function("sfc", 1, 1, sizeof(code), code);
}


inline Function Expn()
{
    static uint8_t code[] = {
        0xd9, 0xf4,                                 // fxtract
        0xdd, 0xd8                                  // fstp        st(0)
    };
    return Function("expn", 1, 1, sizeof(code), code);
}


inline Function Sign()
{
    static uint8_t code[]  =  {
        0xd9, 0xee,                                 // fldz
        0xdf, 0xf1,                                 // fcomip      st, st(1)
        0xdd, 0xd8,                                 // fstp        st(0)
        0xd9, 0xe8,                                 // fld1
        0xd9, 0xe8,                                 // fld1
        0xd9, 0xe0,                                 // fchs
        0xda, 0xc1,                                 // fcmovb      st, st(1)
        0xdd, 0xd9                                  // fstp        st(1)
    };
    return Function("sign", 1, 1, sizeof(code), code);
}


inline Function Signp()
{
    static uint8_t code[]  =  {
        0xd9, 0xe8,                                 // fld1
        0xd9, 0xee,                                 // fldz
        0xdb, 0xf2,                                 // fcomi       st, st(2)
        0xdd, 0xda,                                 // fstp        st(2)
        0xdb, 0xc1,                                 // fcmovnb     st, st(1)
        0xdd, 0xd9                                  // fstp        st(1)
    };
    return Function("signp", 1, 2, sizeof(code), code);
}


inline Function Sqrt()
{
    static uint8_t code[] = {
        0xd9, 0xfa                                  // fsqrt
    };
    return Function("sqrt", 1, 0, sizeof(code), code);
}


inline
void pow_optimizer(elist_it_t it, evaluator* ev, elist_t* elist)
{
    auto f = static_pointer_cast<Function>(*it);

    if ((*f->args[0])->element_type == CCONST) {
        auto v = static_pointer_cast<Constant>(*f->args[0]);

        double v_d = v->get_data_as_double();
        double r_d = round(v_d);
        double a_d = abs(v_d);

        bool matched = true;
        mexce_charstream s;

        // a special case, that the exponent is 0.5
        if (v_d == 0.5) {
            s < 0xd9 < 0xfa;                // fsqrt
        }
        else
        if (r_d == v_d && a_d <= 65536.0) {

            // find the closest power of two
            uint32_t npo2 = (uint32_t)a_d;
            npo2--;
            npo2 |= npo2 >> 1;
            npo2 |= npo2 >> 2;
            npo2 |= npo2 >> 4;
            npo2 |= npo2 >> 8;
            npo2 |= npo2 >> 16;
            npo2++;
            npo2>>=1;

            double diff_high = npo2*2 - a_d;
            double diff_low  = a_d - npo2;

            if (a_d == 0.0) {
                s < 0xdd < 0xd8             // fstp st(0)
                  < 0xd9 < 0xe8;            // fld1
            }
            else
            if (a_d == 1.0) {
                // do nothing
            }
            else
            if (diff_high < 28 &&  diff_low < 28) {
                if (diff_high && diff_low) {
                    // the exponent is not an exact po2, thus we will have to multiply
                    // or divide to get to the result, thus we keep the base in st(1)
                    s < 0xd9 < 0xc0;        // fld  st(0)
                }
                while (npo2 >>= 1) {        // multiply to reach npo2
                    s < 0xdc < 0xc8;        // fmul st(0)
                }

                if (diff_high < diff_low) {
                    s < 0xdc < 0xc8;        // fmul st(0)

                    // divide as many times as the difference
                    // and then get rid of the temporary
                    if (diff_high > 0.0) {
                        while (--diff_high) {
                            s < 0xd8 < 0xf1;    // fdivr  st(0), st(1)
                        }
                        s < 0xde < 0xf1;        // fdivrp st(1), st(0)
                    }
                }
                else {
                    // multiply as many times as the difference
                    // and then get rid of the temporary
                    if (diff_low > 0) {
                        while (--diff_low) {
                            s < 0xd8 < 0xc9;    // fmul  st(0), st(1)
                        }
                        s < 0xde < 0xc9;        // fmulp st(1), st(0)
                    }
                }

                if (diff_high &&  diff_low) {
                    // now we get rid of the temporary we used earlier
                    s < 0xde < 0xc9;            // fmulpst(1), st(0)
                }
            }
            else {
                matched = false;
            }

            if (matched && v_d < 0) {
                s < 0xd9 < 0xe8                 // fld1
                  < 0xde < 0xf1;                // fdivrp  st(1),st   // inverse
            }
        }
        else {
            matched = false;
        }

        if (!matched) {
            // this is almost the generic pow, except that it does not try to figure out
            // if the exponent is an integer

            s < 0xd9 < 0xc9                         // fxch                                 }
              < 0xd9 < 0xe4                         // ftst                                 }
              < 0x9b                                // wait                                 } if base is 0, leave it in st(0)
              < 0xdf < 0xe0                         // fnstsw      ax                       } and exit
              < 0x9e                                // sahf                                 }
              < 0x74 < 0x14                         // je          store_and_exit           }
              < 0xd9 < 0xe1                         // fabs
              < 0xd9 < 0xf1                         // fyl2x                                }
              < 0xd9 < 0xe8                         // fld1                                 }
              < 0xd9 < 0xc1                         // fld         st(1)                    }
              < 0xd9 < 0xf8                         // fprem                                } b^n = 2^(n*log2(b))
              < 0xd9 < 0xf0                         // f2xm1                                }
              < 0xde < 0xc1                         // faddp       st(1), st                }
              < 0xd9 < 0xfd                         // fscale                               }
              < 0x77 < 0x02                         // ja          store_and_exit
              < 0xd9 < 0xe0                         // fchs
// store_and_exit:
              < 0xdd < 0xd9;                        // fstp        st(1)
        }


        uint8_t* cc = push_intermediate_code(ev, s.s.str());
        auto f_opt = make_shared<Function>("pow_opt", 2-matched, 0, s.s.str().size(), cc, nullptr);

        if (matched) {
            f_opt->args[0] = f->args[1];
            elist->erase(f->args[0]);
        }
        else {
            f_opt->args[0] = f->args[0];
            f_opt->args[1] = f->args[1];
        }
        *it = f_opt;
    }
}


inline Function Pow()
{
    static uint8_t code[]  =  {
        0xd9, 0xc0,                                 // fld         st(0)                    }
        0xd9, 0xfc,                                 // frndint                              }
        0xd8, 0xd1,                                 // fcom        st(1)                    } if (abs(exponent) != round(abs(exponent)))
        0xdf, 0xe0,                                 // fnstsw      ax                       }    goto generic_pow;
        0x9e,                                       // sahf                                 }
        0x75, 0x3c,                                 // jne         pop_before_generic_pow   }

        0xd9, 0xe1,                                 // fabs                                 }
        0x66, 0xc7, 0x44, 0x24, 0xfe, 0xff, 0xff,   // mov         word ptr [esp-2],0ffffh  }
        0xdf, 0x5c, 0x24, 0xfe,                     // fistp       word ptr [esp-2]         }
        0x66, 0x8b, 0x44, 0x24, 0xfe,               // mov         ax, word ptr [esp-2]     } if (abs(exponent) > 32)
        0x66, 0x83, 0xe8, 0x01,                     // sub         ax, 1                    }    goto generic_pow;
        0x66, 0x83, 0xf8, 0x21,                     // cmp         ax, 1fh                  } 
        0x77, 0x22,                                 // ja          generic_pow              }

        0xd9, 0xc1,                                 // fld         st(1)
// loop_start:
        0x66, 0x85, 0xc0,                           // test        ax, ax  
        0x74, 0x08,                                 // je          loop_end
        0xdc, 0xca,                                 // fmul        st(2), st  
        0x66, 0x83, 0xe8, 0x01,                     // sub         ax, 1
        0xeb, 0xf3,                                 // jmp         loop_start

// loop_end:

        0xdd, 0xd8,                                 // fstp        st(0)                    }
        0xd9, 0xe4,                                 // ftst                                 }
        0xdf, 0xe0,                                 // fnstsw      ax                       } if the exponent was NOT negative
        0x9e,                                       // sahf                                 }     goto exit_point
        0xdd, 0xd8,                                 // fstp        st(0)                    }
        0x77, 0x28,                                 // ja          exit_point               }

        0xd9, 0xe8,                                 // fld1                                 }
        0xde, 0xf1,                                 // fdivrp      st(1),st                 } inverse
        0xeb, 0x22,                                 // jmp         exit_point               }

// pop_before_generic_pow:
        0xdd, 0xd8,                                 // fstp        st(0)
// generic_pow:
        0xd9, 0xc9,                                 // fxch                                 }
        0xd9, 0xe4,                                 // ftst                                 }
        0x9b,                                       // wait                                 } if base is 0, leave it in st(0)
        0xdf, 0xe0,                                 // fnstsw      ax                       } and exit
        0x9e,                                       // sahf                                 }
        0x74, 0x14,                                 // je          store_and_exit           }
        0xd9, 0xe1,                                 // fabs
        0xd9, 0xf1,                                 // fyl2x                                }
        0xd9, 0xe8,                                 // fld1                                 }
        0xd9, 0xc1,                                 // fld         st(1)                    }
        0xd9, 0xf8,                                 // fprem                                } b^n = 2^(n*log2(b))
        0xd9, 0xf0,                                 // f2xm1                                }
        0xde, 0xc1,                                 // faddp       st(1), st                }
        0xd9, 0xfd,                                 // fscale                               }
        0x77, 0x02,                                 // ja          store_and_exit
        0xd9, 0xe0,                                 // fchs
// store_and_exit:
        0xdd, 0xd9,                                 // fstp        st(1)
// exit_point:
    };
    return Function("pow", 2, 1, sizeof(code), code, pow_optimizer);
}


inline Function Exp()
{
    static uint8_t code[]  =  {
        0xd9, 0xea,                                 // fldl2e  
        0xde, 0xc9,                                 // fmulp       st(1), st  
        0xd9, 0xe8,                                 // fld1  
        0xd9, 0xc1,                                 // fld         st(1)  
        0xd9, 0xf8,                                 // fprem  
        0xd9, 0xf0,                                 // f2xm1  
        0xde, 0xc1,                                 // faddp       st(1), st  
        0xd9, 0xfd,                                 // fscale  
        0xdd, 0xd9,                                 // fstp        st(1)
    };
    return Function("exp", 1, 1, sizeof(code), code);
}


inline Function Logb()  // implementation with base
{
    static uint8_t code[]  =  {
        0xd9, 0xe8,                                 // fld1
        0xd9, 0xc9,                                 // fxch        st(1)
        0xd9, 0xf1,                                 // fyl2x
        0xd9, 0xc9,                                 // fxch        st(1)
        0xd9, 0xe8,                                 // fld1
        0xd9, 0xc9,                                 // fxch        st(1)
        0xd9, 0xf1,                                 // fyl2x
        0xde, 0xf9                                  // fdivp       st(1),st
    };
    return Function("logb", 2, 1, sizeof(code), code);
}


inline Function Ln()
{
    static uint8_t code[]  =  {
        0xd9, 0xe8,                                 // fld1
        0xd9, 0xc9,                                 // fxch        st(1)
        0xd9, 0xf1,                                 // fyl2x
        0xd9, 0xea,                                 // fldl2e
        0xde, 0xf9                                  // fdivp       st(1),st
    };
    return Function("ln", 1, 1, sizeof(code), code);
}


// this is an alias, because of C's math.h
inline Function Log()
{
    Function f = Ln();
    f.name="log";
    return f;
}


inline Function Log10()
{
    static uint8_t code[]  =  {
        0xd9, 0xe8,                                 // fld1
        0xd9, 0xc9,                                 // fxch        st(1)
        0xd9, 0xf1,                                 // fyl2x
        0xd9, 0xe9,                                 // fldl2t
        0xde, 0xf9                                  // fdivp       st(1),st
    };
    return Function("log10", 1, 1, sizeof(code), code);
}


inline Function Log2()
{
    static uint8_t code[] = {
        0xd9, 0xe8,                                 // fld1
        0xd9, 0xc9,                                 // fxch        st(1)
        0xd9, 0xf1                                  // fyl2x
    };
    return Function("log2", 1, 0, sizeof(code), code);
}


inline Function Ylog2()
{
    static uint8_t code[] = {
        0xd9, 0xf1                                  // fyl2x
    };
    return Function("ylog2", 2, 0, sizeof(code), code);
}


inline Function Max()
{
    static uint8_t code[] = {
        0xdb, 0xf1,                                 // fcomi       st,st(1)
        0xda, 0xc1,                                 // fcmovb      st,st(1)
        0xdd, 0xd9                                  // fstp        st(1)
    };
    return Function("max", 2, 0, sizeof(code), code);
}


inline Function Min()
{
    static uint8_t code[] = {
        0xdb, 0xf1,                                 // fcomi       st,st(1)
        0xd9, 0xc9,                                 // fxch        st(1)
        0xda, 0xc1,                                 // fcmovb      st,st(1)
        0xdd, 0xd9                                  // fstp        st(1)
    };
    return Function("min", 2, 0, sizeof(code), code);
}


inline Function Floor()
{
    static uint8_t code[] = {
        0x66, 0xc7, 0x44, 0x24, 0xfc, 0x7f, 0x06,   // mov         word ptr [esp-4], 67fh
        0xd9, 0x7c, 0x24, 0xfe,                     // fnstcw      word ptr [esp-2]
        0xd9, 0x6c, 0x24, 0xfc,                     // fldcw       word ptr [esp-4]
        0xd9, 0xfc,                                 // frndint
        0xd9, 0x6c, 0x24, 0xfe                      // fldcw       word ptr [esp-2]
    };
    return Function("floor", 1, 0, sizeof(code), code);
}


inline Function Ceil()
{
    static uint8_t code[] = {
        0x66, 0xc7, 0x44, 0x24, 0xfc, 0x7f, 0x0a,   // mov         word ptr [esp-4], a7fh
        0xd9, 0x7c, 0x24, 0xfe,                     // fnstcw      word ptr [esp-2]
        0xd9, 0x6c, 0x24, 0xfc,                     // fldcw       word ptr [esp-4]
        0xd9, 0xfc,                                 // frndint
        0xd9, 0x6c, 0x24, 0xfe                      // fldcw       word ptr [esp-2]
    };
    return Function("ceil", 1, 0, sizeof(code), code);
}


inline Function Round()
{
    static uint8_t code[] = {

        // NOTE: In this case, saving/restoring the control word is most likely redundant.

        0x66, 0xc7, 0x44, 0x24, 0xfc, 0x7f, 0x02,   // mov         word ptr [esp-4], 27fh
        0xd9, 0x7c, 0x24, 0xfe,                     // fnstcw      word ptr [esp-2]
        0xd9, 0x6c, 0x24, 0xfc,                     // fldcw       word ptr [esp-4]
        0xd9, 0xfc,                                 // frndint
        0xd9, 0x6c, 0x24, 0xfe                      // fldcw       word ptr [esp-2]
    };
    return Function("round", 1, 0, sizeof(code), code);
}


inline Function Int()
{
    static uint8_t code[] = {
        0xd9, 0xfc                                  // frndint
    };
    return Function("int", 1, 0, sizeof(code), code);
}


inline Function Mod()
{
    static uint8_t code[] = {
        0xd9, 0xc9,                                 // fxch        st(1)
        0xd9, 0xf8,                                 // fprem
        0xdd, 0xd9                                  // fstp        st(1)
    };
    return Function("mod", 2, 0, sizeof(code), code);
}


inline Function Less_than()
{
    static uint8_t code[] = {
        0xdf, 0xf1,                                 // fcomip      st,st(1)  
        0xdd, 0xd8,                                 // fstp        st(0)  
        0xd9, 0xe8,                                 // fld1  
        0xd9, 0xee,                                 // fldz  
        0xdb, 0xd1,                                 // fcmovnb     st,st(1)  
        0xdd, 0xd9,                                 // fstp        st(1)  
    };
    return Function("less_than", 2, 0, sizeof(code), code);
}


inline Function Bnd()
{
    static uint8_t code[] = {
        0xd9, 0xc9,                                 // fxch        st(1)
        0xd9, 0xf8,                                 // fprem
        0xd9, 0xc0,                                 // fld         st(0)
        0xdc, 0xc2,                                 // fadd        st(2), st
        0xd9, 0xee,                                 // fldz
        0xdf, 0xf1,                                 // fcomip      st,st(1)
        0xdd, 0xd8,                                 // fstp        st(0)
        0xdb, 0xc1,                                 // fcmovnb     st,st(1)
        0xdd, 0xd9                                  // fstp        st(1)
    };
    return Function("bnd", 2, 2, sizeof(code), code);
}


inline
pair<elist_it_t, elist_it_t> get_dependent_chunk(elist_it_t it)
{
    auto it_end = next(it);
    while ( (*it) ->element_type == CFUNC) {
        shared_ptr<Function> f = static_pointer_cast<Function>( *it );
        if (!f->args.size()) {
            break;
        }
        it = f->args[f->args.size()-1];
    }
    return make_pair(it, it_end);
}


struct elist_comparison {
    bool operator()(const elist_t& a, const elist_t& b) const {

        // empty element lists cannot exist
        assert(a.size() && b.size());

        // if their size differs, we use that for comparison
        if (a.size() != b.size()) {
            return a.size() > b.size();
        }

        // they are the same size, thus we need to traverse both
        auto ita = a.begin();
        auto itb = b.begin();
        for (; ita != a.end(); ita++, itb++) {
            // start by comparing element types
            if ((*ita)->element_type != (*itb)->element_type) {
                return (*ita)->element_type > (*itb)->element_type;
            }

            // if they are constants, we compare the values
            if ((*ita)->element_type == CCONST) {
                double da = static_pointer_cast<Constant>(*ita)->get_data_as_double();
                double db = static_pointer_cast<Constant>(*itb)->get_data_as_double();
                if (da != da && db != db) { // i.e. if both of them are NaN
                    // not all NaNs are the same, we compare binary
                    auto mcr = memcmp(&da, &db, sizeof(double));
                    if (mcr != 0) {
                        return mcr < 0;
                    }
                }
                else
                if (da != db) {
                    return da < db;
                }
                continue; // it is the same... move on
            }

            // if they are variables, we compare addresses
            if ((*ita)->element_type == CVAR) {
                volatile void* aa = static_pointer_cast<Variable>(*ita)->address;
                volatile void* ab = static_pointer_cast<Variable>(*itb)->address;
                if (aa != ab) {
                    return aa < ab;
                }
                continue; // it is the same... move on
            }

            // if they are functions, we compare their code
            if ((*ita)->element_type == CFUNC) {
                string fna = static_pointer_cast<Function>(*ita)->code;
                string fnb = static_pointer_cast<Function>(*itb)->code;

                if (fna != fnb) {
                    return fna < fnb;
                }
                continue; // it is the same... move on [this one is not really required]
            }
        }

        return false; // they are equal
    }
};



template <uint8_t OP>
void emit_apply_op_with_value(impl::mexce_charstream& s, shared_ptr<impl::Value> v)
{
    using namespace impl;
#ifdef MEXCE_64
    s < 0x48 < 0xb8;                        // mov            rax, qword ptr
#else
    s < 0xb8;                               // mov            eax, dword ptr
#endif
    s << v->address;                        //                   [the address]
    switch(v->numeric_data_type) {
        case M16INT: s < 0xde < OP; break;  // f[OP]  word  ptr [eax/rax]  
        case M32INT: s < 0xda < OP; break;  // f[OP]  dword ptr [eax/rax]  
        case M32FP:  s < 0xd8 < OP; break;  // f[OP]  dword ptr [eax/rax]
        case M64FP:  s < 0xdc < OP; break;  // f[OP]  qword ptr [eax/rax]

        // the FPU has limited support for 64-bit integers and M64INT cannot be supported here
        default: assert(false);
    }
}


template <uint8_t OP>
void emit_apply_op_with_constant(evaluator* ev, impl::mexce_charstream& s, double v)
{
    emit_apply_op_with_value<OP>(s, impl::make_intermediate_constant(ev, v));
}



inline
void emit_load_constant(evaluator* ev, impl::mexce_charstream& s, double v)
{
    using namespace impl;

    double av = abs(v);
    bool hit = false;

    if (av == 0.0)                         { s < 0xd9 < 0xee; hit = true; } else  // fldz
    if (av == 1.0)                         { s < 0xd9 < 0xe8; hit = true; } else  // fld1
    if (av == 3.1415926535897932384626433) { s < 0xd9 < 0xeb; hit = true; } else  // fldpi
    if (av == 3.32192809488736234787)      { s < 0xd9 < 0xe9; hit = true; } else  // fldl2t
    if (av == 1.44269504088896340736)      { s < 0xd9 < 0xea; hit = true; } else  // fldl2e
    if (av == 0.3010299956639811952137)    { s < 0xd9 < 0xec; hit = true; } else  // fldlg2
    if (av == 0.6931471805599453094172)    { s < 0xd9 < 0xed; hit = true; }       // fldln2

    if (hit) {
        if (v < 0) {
            s < 0xd9 < 0xe0;  // fchs
        }
        return;
    }

    auto sc = make_intermediate_constant(ev, v);

#ifdef MEXCE_64
    s < 0x48 < 0xb8;                            // mov            rax, qword ptr
    s << (void*)(sc->address);
    s < 0xdd < 0x00;                            // fld            [rax]
#else
    s < 0xdd < 0x05;                            // fld            [immediate address]
    s << (void*)(sc->address);
#endif
}



inline
void compile_elist(impl::mexce_charstream& code_buffer, const impl::elist_const_it_t first, const impl::elist_const_it_t last)
{
    using namespace impl;

    elist_const_it_t it = first;

    for (; it != last; it++) {
        if ((*it)->element_type == CVAR  ||
            (*it)->element_type == CCONST)
        {
            Value * tn = (Value *) it->get();

#ifdef MEXCE_64
            code_buffer << (uint16_t)0xb848;   // move input address to rax (opcode)
            code_buffer << (void*)tn->address;
#endif

            switch (tn->numeric_data_type) {
#ifdef MEXCE_64
                // On x64, variable addresses are already supplied in rax.
                case M32FP:   code_buffer < 0xd9 < 0x00; break;
                case M64FP:   code_buffer < 0xdd < 0x00; break;
                case M16INT:  code_buffer < 0xdf < 0x00; break;
                case M32INT:  code_buffer < 0xdb < 0x00; break;
                case M64INT:  code_buffer < 0xdf < 0x28; break;
#else
                // On 32-bit x86, variable addresses are explicitly specified.
                case M32FP:   code_buffer < 0xd9 < 0x05; break;
                case M64FP:   code_buffer < 0xdd < 0x05; break;
                case M16INT:  code_buffer < 0xdf < 0x05; break;
                case M32INT:  code_buffer < 0xdb < 0x05; break;
                case M64INT:  code_buffer < 0xdf < 0x2d; break;
#endif
            }

#ifndef MEXCE_64
            code_buffer << (void*)(tn->address);
#endif
        }
        else {
            Function * tf = (Function *) it->get();
            code_buffer.s.write(tf->code.data(), tf->code.size());
        }
    }
}



inline shared_ptr<Function> make_function(const string& name);


inline string infix_operator_to_function_name(const string& op)
{
    static map<string, string> op_map = {
        { "+", "add" },
        { "-", "sub" },
        { "*", "mul" },
        { "/", "div" },
        { "^", "pow" },
        { "<", "less_than" }
    };
    auto it = op_map.find(op);
    assert(it != op_map.end());
    return it->second;
}


inline string function_name_to_infix_operator(const string& fn)
{
    static map<string, string> op_map = {
        { "add", "+" },
        { "sub", "-" },
        { "mul", "*" },
        { "div", "/" },
        { "pow", "^" },
        { "less_than", "<" }
    };
    auto it = op_map.find(fn);
    if (it == op_map.end()) {
        return "";
    }
    return it->second;
}


inline string function_name_to_unary_operator(const string& fn)
{
    if (fn == "neg")
        return "-";
    return "";
}


inline
string double_to_pretty_string(double v)
{
    stringstream ss;
    ss << v;
    return ss.str();
}


inline
string elist_to_string(const elist_t& elist)
{

    deque<std::tuple<string, size_t, vector<string>>> st;

    // root element appears as an unnamed function of 1 argument
    st.push_back(make_tuple(string(), 2, vector<string>{""}));

    for (auto it = elist.rbegin(); it != elist.rend(); it++) {
        auto e = *it;
        if (e->element_type == CFUNC) {
            auto f = static_pointer_cast<Function>(e);
            st.push_back(make_tuple(string(), f->args.size() + 1, vector<string>{f->name} ));
        }
        else
        if (e->element_type == CCONST) {
            auto c = static_pointer_cast<Constant>(e);
            get<2>(st.back()).push_back( double_to_pretty_string(c->get_data_as_double()) );
        }
        else
        if (e->element_type == CVAR) {
            auto v = static_pointer_cast<Variable>(e);
            get<2>(st.back()).push_back( v->name );
        }

        while ( get<2>(st.back()).size() ==  get<1>(st.back()) ) {
            string& lrs = get<0>(st.back());
            vector<string>& lrv = get<2>(st.back());

            string symbolic_op;
            if ( (get<1>(st.back()) == 2) && !(symbolic_op = function_name_to_unary_operator(lrv[0])).empty() ) {
                lrs = string("(") + symbolic_op + lrv.back() + ")";
            }
            else
            if ( (get<1>(st.back()) == 3) && !(symbolic_op = function_name_to_infix_operator(lrv[0])).empty() ) {
                lrs = string("(") + lrv.back() + symbolic_op;
                lrv.pop_back();
                lrs += lrv.back() + ")";
            }
            else {
                lrs += lrv[0] + "(";
                if (lrv.size() != 1) {
                    while (true) {
                        lrs += lrv.back();
                        lrv.pop_back();
                        if (lrv.size() == 1) {
                            break;
                        }
                        lrs += ", ";
                    }
                }
                lrs += ")";
            }

            if (st.size()!=1) {
                string tmp = lrs;
                st.pop_back();
                get<2>(st.back()).push_back(tmp);
            }
        }
    }

    assert(st.size() == 1);
    string ret = get<0>(st.back());
    return ret.substr(1, ret.size()-2);
}


inline
void asmd_optimizer(elist_it_t it, evaluator* ev, elist_t* elist)
{
    auto f = static_pointer_cast<Function>(*it);
    auto fname = string(f->name);
    int fclass = (fname == "add" || fname == "sub") ? 1 : (fname == "mul" || fname == "div") ? 2 : 0;
    assert(fclass);

    double neutral = fclass==1 ? 0.0 : 1.0;


    bool arg2_inv = (fname == "sub" || fname == "div");

    if (f->parent != elist->end() &&  (*f->parent)->element_type == CFUNC) {
        shared_ptr<Function> pf = static_pointer_cast<Function>(*f->parent);
        auto pname = string(pf->name);
        int pclass = (pname == "add" || pname == "sub") ? 1 : (pname == "mul" || pname == "div") ? 2 : 0;
        bool parg2_inv = (pname == "sub" || pname == "div");

        if (pclass && pclass == fclass) {

            // the function will be absorbed by its parent

            bool parent_inv_op = f->parent_arg_index == 0 && parg2_inv; // arg 0 in postfix, is the second infix argument

            // this is the first infix argument (postfix order is inverse)
            auto arg1_chunk = get_dependent_chunk(f->args[1]);
            pf->absorbed[parent_inv_op           ].push_back(elist_t(arg1_chunk.first, arg1_chunk.second));
            elist->erase(arg1_chunk.first, arg1_chunk.second);

            // the second infix argument
            auto arg0_chunk = get_dependent_chunk(f->args[0]);
            pf->absorbed[parent_inv_op ^ arg2_inv].push_back(elist_t(arg0_chunk.first, arg0_chunk.second));
            elist->erase(arg0_chunk.first, arg0_chunk.second);

            pf->absorbed[ parent_inv_op].insert(pf->absorbed[ parent_inv_op].end(),
                f->absorbed[0].begin(), f->absorbed[0].end() );
            pf->absorbed[!parent_inv_op].insert(pf->absorbed[!parent_inv_op].end(),
                f->absorbed[1].begin(), f->absorbed[1].end() );

            pf->force_not_constant = true;

            *it = make_shared<Constant>( neutral );

            return;
        }
    }

    // end of chain - simplify and generate code

    // accumulate own args

    // first infix argument
    auto arg1_chunk = get_dependent_chunk(f->args[1]);
    f->absorbed[0       ].push_back(elist_t(arg1_chunk.first, arg1_chunk.second));
    elist->erase(arg1_chunk.first, arg1_chunk.second);

    // second infix argument
    auto arg0_chunk = get_dependent_chunk(f->args[0]);
    f->absorbed[arg2_inv].push_back(elist_t(arg0_chunk.first, arg0_chunk.second));
    elist->erase(arg0_chunk.first, arg0_chunk.second);

    // at this point, this is a function of 0 arguments, all of them were absorbed
    f->args.clear();

    // reduce constants
    double ac[2] = {neutral, neutral};
    for (int i=0; i<2; i++) {
        for (auto e = f->absorbed[i].begin(); e!=f->absorbed[i].end(); ) {
            auto next_e = next(e);
            if (e->size()==1 && e->front()->element_type == CCONST) {
                auto v = static_pointer_cast<Constant>(e->front());
                if (fclass==1) {
                    ac[i] += *((double*)v->address);
                }
                else {
                    ac[i] *= *((double*)v->address);
                }
                f->absorbed[i].erase(e);
            }
            e = next_e;
        }
    }
    double ac_final = (fclass==1) ? (ac[0] -ac[1]) : (ac[0] * 1.0/ac[1]);

    // sort and gather chunks
    map<elist_t, int, elist_comparison> sig_map;
    for (auto &e : f->absorbed[0]) { sig_map[e]++; }
    for (auto &e : f->absorbed[1]) { sig_map[e]--; }

    mexce_charstream s;

    // TODO: assert that none of the values are constant

    if (fclass==1) {    // NOTE: children can be mul/div, but they cannot be add/sub

        bool constant_added = false;
        bool fpu_stack_empty = true;

        for (auto &e : sig_map) {

            if (e.second == 0) {
                // factor 0 in add_sum means 0*a and in multiplications
                // it means a^0, in both of which cases it has no effect.
                continue;
            }

            // if the stack is not empty and the elist is only one element and the
            // factor in e.second is 1 or -1,
            // we can multiply directly from memory, to save one place in the FPU
            // stack. This is a tradeoff, as it might be slightly slower to do so.

            if (!fpu_stack_empty && next(e.first.begin()) == e.first.end() && abs(e.second)==1.0 &&
                (e.first.front()->element_type == CCONST || e.first.front()->element_type == CVAR) )
            {
                auto v = static_pointer_cast<Value>(e.first.front());
                if (v->numeric_data_type != M64INT) { // see emit_apply_op_with_value implementation
                    if (e.second == 1) {
                        emit_apply_op_with_value<0x00>(s, v);
                    }
                    else {
                        emit_apply_op_with_value<0x20>(s, v);
                    }
                    continue;
                }
            }

            compile_elist(s, e.first.begin(), e.first.end());
            fpu_stack_empty = false;

            if (e.second == 1) {
                // 1*a == a
                // we loaded the expression, there is nothing further to do                
            }
            else
            if (e.second == -1) {
                s < 0xd9 < 0xe0;  // fchs
            }
            else
            if (e.second == 2) {
                s < 0xd8 < 0xc0;  // fadd st(0), st(0)
            }
            else
            if (e.second == -2) {
                s < 0xd8 < 0xc0;  // fadd st(0), st(0)
                s < 0xd9 < 0xe0;  // fchs
            }
            else {
                emit_apply_op_with_constant<0x08>(ev, s, e.second);
            }

            if (!constant_added) {
                // add the constant

                // doing this here and not in the beginning requires one place
                // less in the fpu stack (and 1 instruction less too)

                if (ac_final != neutral) {
                    emit_apply_op_with_constant<0x00>(ev, s, ac_final);
                }
                constant_added = true;
            }
            else {
                s < 0xde < 0xc1;  // faddp       st(1), st
            }
        }

        if (fpu_stack_empty) { // we did nothing, we should at least load a zero
            s < 0xd9 < 0xee;   // fldz
        }
    }
    else {
        // NOTE: children can be powers, but they cannot be mul/div.
        // They can also be add/sub, but this is not interesting for optimization.

        bool constant_multiplied = false;
        bool fpu_stack_empty = true;

        for (auto &e : sig_map) {

            if (e.second == 0) {
                // factor 0 in add_sum means 0*a and in multiplications
                // it means a^0, in both of which cases it has no effect.
                continue;
            }

            // if the stack is not empty and the elist is only one element and the
            // factor in e.second is 1 or -1,
            // we can multiply directly from memory, to save one place in the FPU
            // stack. This is a tradeoff, as it might be slightly slower to do so.

            if (!fpu_stack_empty && next(e.first.begin()) == e.first.end() && abs(e.second)==1.0 &&
                (e.first.front()->element_type == CCONST || e.first.front()->element_type == CVAR) )
            {
                auto v = static_pointer_cast<Value>(e.first.front());
                if (v->numeric_data_type != M64INT) { // see emit_apply_op_with_value implementation
                    if (e.second == 1) {
                        emit_apply_op_with_value<0x08>(s, v);
                    }
                    else {
                        emit_apply_op_with_value<0x30>(s, v);
                    }
                    continue;
                }
            }

            compile_elist(s, e.first.begin(), e.first.end());
            fpu_stack_empty = false;

            if (e.second == 1) {
                // a^1 == a
                // we loaded the expression, there is nothing further to do                
            }
            else
            if (e.second == -1) {   //  1/a
                s < 0xd9 < 0xe8;    // fld1
                s < 0xde < 0xf1;    // fdivrp   st(1), st
            }
            else
            if (e.second == 2) {    //  a*a
                s < 0xdc < 0xc8;    // fmul st(0), st(0)
            }
            else
            if (e.second == -2) {   //  1/(a*a)
                s < 0xdc < 0xc8;    // fmul st(0), st(0)
                s < 0xd9 < 0xe8;    // fld1
                s < 0xde < 0xf1;    // fdivrp   st(1), st
            }
            else {
                elist_t pow_list = e.first;
                pow_list.push_back(make_intermediate_constant(ev, e.second));
                auto pow_f = make_function("pow");
                pow_list.push_back(pow_f);
                link_arguments(pow_list);
                pow_f->optimizer(prev(pow_list.end()), ev, &pow_list);

                compile_elist(s, pow_list.begin(), pow_list.end());
            }

            if (!constant_multiplied) {
                // add the constant

                // doing this here and not in the beginning requires one place
                // less in the fpu stack (and 1 instruction less too)

                if (ac_final != neutral) {
                    emit_apply_op_with_constant<0x08>(ev, s, ac_final);
                }
                constant_multiplied = true;
            }
            else {
                s < 0xde < 0xc9;                       // fmulp       st(1), st
            }
        }

        if (fpu_stack_empty) { // we did nothing, we should at least load 1
            s < 0xd9 < 0xe8; 
        }
    }

    string new_name = (fclass == 1) ? "add_sub_opt" : "mul_div_opt";

    uint8_t* cc = push_intermediate_code(ev, s.s.str());
    auto f_opt = make_shared<Function>(new_name, 0, 0, s.s.str().size(), cc, nullptr);
    
    *it = f_opt;
    return;
}


inline Function Add()
{
    static uint8_t code[] = {
        0xde, 0xc1                                  // faddp       st(1), st
    };
    return Function("add", 2, 0, sizeof(code), code, asmd_optimizer);
}


inline Function Sub()
{
    static uint8_t code[] = {
        0xde, 0xe9                                  // fsubp       st(1), st
    };
    return Function("sub", 2, 0, sizeof(code), code, asmd_optimizer);
}


inline Function Mul()
{
    static uint8_t code[] = {
        0xde, 0xc9                                  // fmulp       st(1), st
    };
    return Function("mul", 2, 0, sizeof(code), code, asmd_optimizer);
}


inline Function Div()
{
    static uint8_t code[] = {
        0xde, 0xf9                                  // fdivp       st(1), st
    };
    return Function("div", 2, 0, sizeof(code), code, asmd_optimizer);
}


inline Function Neg()
{
    // TODO: this does not need its own internal name, it is a special case of add_sub
    static uint8_t code[] = {
        0xd9, 0xe0                                  // fchs
    };
    return Function("neg", 1, 0, sizeof(code), code);
}


inline Function Gain()
{
    //                            x
    //                 ------------------------  if x < 0.5
    //                 (1 / a - 2) (1 - 2x) + 1
    // gain(x, a) =                                               for x, a in [0, 1]
    //                 (1 / a - 2) (1 - 2x) - x
    //                 ------------------------  if x >= 0.5
    //                 (1 / a - 2) (1 - 2x) - 1

    static uint8_t code[] = {                       //                       ; FPU stack
        0xd9, 0xc1,                                 // fld         st(1)     ; x, a, x
        0xd8, 0xc2,                                 // fadd        st,st(2)  ; 2x, a, x
        0xd9, 0xe8,                                 // fld1                  ; 1, 2x, a, x
        0xdf, 0xf1,                                 // fcomip      st,st(1)  ; 2x, a, x
        0xdd, 0xd8,                                 // fstp        st(0)     ; a, x
        0xd9, 0xc0,                                 // fld         st(0)     ; a, a, x
        0xd8, 0xc1,                                 // fadd        st,st(1)  ; 2a, a, x
        0xd9, 0xe8,                                 // fld1                  ; 1, 2a, a, x
        0xde, 0xe9,                                 // fsubp       st(1),st  ; 2a-1, a, x
        0xde, 0xf1,                                 // fdivrp      st(1),st  ; (2a-1)/a, x
        0xd9, 0xc1,                                 // fld         st(1)     ; x, (2a-1)/a, x
        0xdc, 0xc0,                                 // fadd        st(0),st  ; 2x, (2a-1)/a, x 
        0xd9, 0xe8,                                 // fld1                  ; 1, 2x, (2a-1)/a, x
        0xde, 0xe9,                                 // fsubp       st(1),st  ; 2x-1, (2a-1)/a, x
        0xde, 0xc9,                                 // fmulp       st(1),st  ; (2x-1)*(2a-1)/a, x
        0xd9, 0xe8,                                 // fld1                  ; 1, (2x-1)*(2a-1)/a, x
        0x72, 0x06,                                 // jb          x_ge_half
        0xde, 0xc1,                                 // faddp       st(1),st  ; (2x-1)*(2a-1)/a+1, x
        0xde, 0xf9,                                 // fdivp       st(1),st  ; x/((2x-1)*(2a-1)/a+1) [result]
        0xeb, 0x0a,                                 // jmp         gain_exit
// x_ge_half:
        0xd9, 0xc1,                                 // fld         st(1)     ; (2x-1)*(2a-1)/a, 1, (2x-1)*(2a-1)/a, x
        0xde, 0xe9,                                 // fsubp       st(1),st  ; 1-(2x-1)*(2a-1)/a, (2x-1)*(2a-1)/a, x
        0xd9, 0xc9,                                 // fxch        st(1)     ; (2x-1)*(2a-1)/a, 1-(2x-1)*(2a-1)/a, x
        0xde, 0xea,                                 // fsubp       st(2),st  ; 1-(2x-1)*(2a-1)/a, x-(2x-1)*(2a-1)/a
        0xde, 0xf9,                                 // fdivp       st(1),st  ; (x-(2x-1)*(2a-1)/a)/(1-(2x-1)*(2a-1)/a)  [result]
// gain_exit:
    };
    return Function("gain", 2, 1, sizeof(code), code);
}


inline Function Bias()
{
    //                         x
    // bias(x, a) = -----------------------    for x, a in [0, 1]
    //              (1 / a - 2) (1 - x) + 1

    static uint8_t code[] = {
        0xd9, 0xe8,                                 // fld1
        0xdc, 0xf1,                                 // fdivr       st(1), st
        0xdc, 0xe9,                                 // fsub        st(1), st
        0xdc, 0xe9,                                 // fsub        st(1), st
        0xd8, 0xe2,                                 // fsub        st, st(2)
        0xde, 0xc9,                                 // fmulp       st(1), st
        0xd9, 0xe8,                                 // fld1
        0xde, 0xc1,                                 // faddp       st(1), st
        0xde, 0xf9                                  // fdivp       st(1), st
    };
    return Function("bias", 2, 1, sizeof(code), code);
}



inline const map<string, Function>& make_function_map()
{
    static Function f[] = {
        Sin(), Cos(), Tan(), Abs(), Sign(), Signp(), Expn(), Sfc(), Sqrt(), Pow(), Exp(), Less_than(),
        Log(), Log2(), Ln(), Log10(), Logb(), Ylog2(), Max(), Min(), Floor(), Ceil(), Round(), Int(), Mod(),
        Bnd(), Add(), Sub(), Neg(), Mul(), Div(), Bias(), Gain()
    };

    static map<string, Function> ret;
    for (auto& e : f) {
        assert(ret.find(e.name) == ret.end()); //if it fails, some functions share the same name.
        ret.insert(make_pair(e.name, e));
    }
    return ret;
}


inline const map<string, Function>& function_map()
{
    static const map<string, Function>& fname_map = make_function_map();
    return fname_map;
}


inline shared_ptr<Function> make_function(const string& name) {
    auto fn = function_map().find(name);
    return make_shared<Function>(fn->second);
}


inline const map<string, shared_ptr<Constant> >& built_in_constants_map()
{
    static const map<string, shared_ptr<Constant> > cname_map = {
        { "pi", std::make_shared<impl::Constant>("3.141592653589793238462643383", "pi") },
        { "e",  std::make_shared<impl::Constant>("2.718281828459045235360287471", "e" ) }
    };
    return cname_map;
}


struct Token
{
    int             type        = 0;
    int             priority    = 0;
    size_t          position    = 0;
    string          content;
    Token() = default;
    Token(int type, size_t position, char content):
        type      ( type               ),
        priority  ( type               ),
        position  ( position           ),
        content   ( string() + content ) {}
};


template <typename> inline Numeric_data_type get_ndt()  { assert(false); }
template <> inline Numeric_data_type get_ndt<double >() { return M64FP;  }
template <> inline Numeric_data_type get_ndt<float  >() { return M32FP;  }
template <> inline Numeric_data_type get_ndt<int16_t>() { return M16INT; }
template <> inline Numeric_data_type get_ndt<int32_t>() { return M32INT; }
template <> inline Numeric_data_type get_ndt<int64_t>() { return M64INT; }


inline bool is_operator(  char c) { return  c=='+' || c=='-'  ||  c=='*' || c=='/'  || c=='^' || c=='<'; }
inline bool is_alphabetic(char c) { return (c>='A' && c<='Z') || (c>='a' && c<='z') || c=='_'; }
inline bool is_numeric(   char c) { return  c>='0' && c<='9'; }


} // mexce_impl


inline
evaluator::evaluator():
    m_constants(impl::built_in_constants_map())
{
    assign_expression("0");
}


inline
evaluator::~evaluator()
{
    impl::free_executable_buffer(evaluate_fptr, m_buffer_size);
}


template <typename T>
void evaluator::bind(T& v, const std::string& s)
{
    using namespace impl;
    if (function_map().find(s) != function_map().end()) {
        throw std::logic_error("Attempted to bind a variable, named as an existing function");
    }
    if (built_in_constants_map().find(s) != built_in_constants_map().end()) {
        throw std::logic_error("Attempted to bind a variable, named as an existing constant");
    }
    m_variables[s] = make_shared<Variable>(&v, s, get_ndt<T>());
}



inline
void evaluator::unbind(const std::string& s)
{
    if (s.length() == 0)
        throw std::logic_error("Variable name was an empty string");

    auto it = m_variables.find(s);
    if (it != m_variables.end()) {
        assert(it->second->element_type == impl::CVAR);
        if (it->second->referenced) {
            assign_expression("0");
        }
        m_variables.erase(it);
        return;
    }
    throw std::logic_error("Attempted to unbind an unknown variable");
}



inline
double evaluator::evaluate() {
    if (is_constant_expression) {
        return constant_expression_value;
    }
    return evaluate_fptr();
}



inline
void evaluator::assign_expression(std::string e)
{
    using namespace impl;
    using mpe = mexce_parsing_exception;

    deque<Token> tokens;

    m_intermediate_constants.clear();
    m_intermediate_code.clear();
    m_elist.clear();

    if (evaluate_fptr) {
        free_executable_buffer(evaluate_fptr, m_buffer_size);
        evaluate_fptr = nullptr;
    }

    auto x = m_variables.begin();
    for (; x != m_variables.end(); x++)
        x->second->referenced = false;

    if (e.length() == 0){
        throw (std::logic_error("Expected an expression"));
    }

    e += ' ';

    //stage 1: checking expression syntax
    Token temp;
    vector< pair<int, int> > bdarray(1);
    map<string, Function>::const_iterator i_fnc;
    int state = 0;
    size_t i = 0;
    int function_parentheses = 0;
    for (; i < e.length(); i++) {
        switch(state) {
            case 0: //start of expression
                if (e[i] == '-' || e[i] == '+') {
                    tokens.push_back(Token(UNARY, i, e[i]));
                    state = 4;
                    break;
                }
                if (e[i] == ')') {
                    if (bdarray.back().first != 0)
                        throw (mpe("Expected an expression", i));
                    if (bdarray.back().second != 0)
                        throw (mpe("Expected more arguments", i));
                    tokens.push_back(Token(FUNCTION_RIGHT_PARENTHESIS, i, ')'));
                    function_parentheses--;
                    bdarray.pop_back();
                    state = 5;
                    break;
                }
            case 4: //just read an infix operator
                if (e[i] == ' ')
                    break;
                if (is_numeric(e[i])) {
                    temp = Token(NUMERIC_LITERAL, i, e[i]);
                    state = 1;
                    break;
                }
                if (e[i] == '.') {
                    temp = Token(NUMERIC_LITERAL, i, e[i]);
                    state = 2;
                    break;
                }
                if (is_alphabetic(e[i])) {
                    temp = Token(0, i, e[i]);
                    state = 3;
                    break;
                }
                if (e[i] == '-' || e[i] == '+') {
                    tokens.push_back(Token(UNARY, i, e[i]));
                    state = 4;
                    break;
                }
                if (e[i] == '(') {
                    tokens.push_back(Token(LEFT_PARENTHESIS, i, '('));
                    bdarray.back().first++;
                    state = 0;
                    break;
                }
                else {
                    throw (mpe((string("\"")+e[i])+"\" not expected", i));
                }
            case 1: //currently reading a numeric literal
                if (e[i] == '.') {
                    temp.content += e[i];
                    state = 2;
                    break;
                }
            case 2: //currently reading a numeric literal, found dot
                if (is_numeric(e[i])) {
                    temp.content += e[i];
                    break;
                }
                if (e[i] == ' ') {
                    tokens.push_back(temp);
                    state = 5;
                    break;
                }
                if (e[i] == ')') {
                    tokens.push_back(temp);
                    if (bdarray.back().first > 0) {
                        tokens.push_back(Token(RIGHT_PARENTHESIS, i, ')'));
                        bdarray.back().first--;
                    }
                    else {
                        if (function_parentheses <= 0)
                            throw (mpe("\")\" not expected", i));
                        if (bdarray.back().second != 1)
                            throw (mpe("Expected more arguments", i));
                        tokens.push_back(Token(FUNCTION_RIGHT_PARENTHESIS, i, ')'));
                        function_parentheses--;
                        bdarray.pop_back();
                    }
                    state = 5;
                    break;
                }
                if (is_operator(e[i])) {
                    tokens.push_back(temp);
                    tokens.push_back(Token( get_infix_rank(e[i]) , i, e[i]));
                    state = 4;
                    break;
                }
                if (e[i] == ',') {
                    tokens.push_back(temp);
                    if (bdarray.back().first != 0)
                        throw (mpe("Expected a \")\"", i));
                    if (bdarray.back().second-- < 2)
                        throw (mpe("Don\'t expect any arguments here", i));
                    tokens.push_back(Token(COMMA, i, ','));
                    state = 0;
                    break;
                }
                else {
                    throw (mpe((string("\"")+e[i])+"\" not expected", i));
                }
            case 3: //currently reading alphanumeric
                if (is_alphabetic(e[i]) || is_numeric(e[i])) {
                    temp.content += e[i];
                    break;
                }
                if (e[i] == ' ') {
                    if (m_variables.find(temp.content) != m_variables.end()) {
                        temp.type = VARIABLE_NAME;
                        tokens.push_back(temp);
                        state = 5;
                    }
                    else
                    if (m_constants.find(temp.content) != m_constants.end()) {
                        temp.type = CONSTANT_NAME;
                        tokens.push_back(temp);
                        state = 5;
                    }
                    else
                    if ((i_fnc = function_map().find(temp.content)) != function_map().end()) {
                        temp.type = FUNCTION_NAME;
                        tokens.push_back(temp);
                        tokens.push_back(Token(FUNCTION_LEFT_PARENTHESIS, i, '('));
                        bdarray.push_back(make_pair(0, i_fnc->second.num_args));
                        function_parentheses++;
                        state = 6;
                    }
                    else {
                        throw (mpe(string(temp.content) +
                            " is not a known constant, variable or function name", i));
                    }
                    break;
                }
                if (e[i] == ')') {
                    temp.type = m_variables.find(temp.content) != m_variables.end() ? VARIABLE_NAME : 
                                m_constants.find(temp.content) != m_constants.end() ? CONSTANT_NAME :
                        throw (mpe(string(temp.content) +
                            " is not a known constant or variable name", i));
                    tokens.push_back(temp);
                    if (bdarray.back().first > 0) {
                        tokens.push_back(Token(RIGHT_PARENTHESIS, i, ')'));
                        bdarray.back().first--;
                    }
                    else
                    if (function_parentheses > 0) {
                        if (bdarray.back().second != 1)
                            throw (mpe("Expected more arguments", i));
                        tokens.push_back(Token(FUNCTION_RIGHT_PARENTHESIS, i, ')'));
                        function_parentheses--;
                        bdarray.pop_back();
                    }
                    else
                        throw (mpe("\")\" not expected", i));
                    state = 5;
                    break;
                }
                if (e[i] == '(') {
                    if ((i_fnc = function_map().find(temp.content)) == function_map().end()) {
                        throw (mpe(string(temp.content) + " is not a known function name", i));
                    }
                    temp.type = FUNCTION_NAME;
                    tokens.push_back(temp);
                    tokens.push_back(Token(FUNCTION_LEFT_PARENTHESIS, i, '('));
                    bdarray.push_back(make_pair(0, i_fnc->second.num_args));
                    function_parentheses++;
                    state = 0;
                    break;
                }
                if (is_operator(e[i])) {
                    temp.type = m_variables.find(temp.content) != m_variables.end() ? VARIABLE_NAME : 
                                m_constants.find(temp.content) != m_constants.end() ? CONSTANT_NAME :
                        throw (mpe(string(temp.content) +
                            " is not a known constant or variable name", i));
                    tokens.push_back(temp);
                    tokens.push_back(Token(get_infix_rank(e[i]), i, e[i]));
                    state = 4;
                    break;
                }
                if (e[i] == ',') {
                    temp.type = m_variables.find(temp.content) != m_variables.end() ? VARIABLE_NAME : 
                                m_constants.find(temp.content) != m_constants.end() ? CONSTANT_NAME :
                        throw (mpe(string(temp.content)+" is not a "
                            "known constant or variable name", i));
                    tokens.push_back(temp);
                    if (bdarray.back().first != 0)
                        throw (mpe("Expected a \")\"", i));
                    if (bdarray.back().second-- < 2)
                        throw (mpe("Don\'t expect any arguments here", i));
                    tokens.push_back(Token(COMMA, i, ','));
                    state = 0;
                    break;
                }
                else {
                    throw (mpe((string("\"")+e[i])+"\" not expected", i));
                }
            case 5: //just read an expression (constant/variable/right parenthesis)
                if (e[i] == ' ')
                    break;
                if (is_operator(e[i])) {
                    tokens.push_back(Token(get_infix_rank(e[i]), i, e[i]));
                    state = 4;
                    break;
                }
                if (e[i] == ')') {
                    if (bdarray.back().first > 0) {
                        tokens.push_back(Token(RIGHT_PARENTHESIS, i, ')'));
                        bdarray.back().first--;
                    }
                    else
                    if (function_parentheses > 0) {
                        if (bdarray.back().second != 1)
                            throw (mpe("Expected more arguments", i));
                        tokens.push_back(Token(FUNCTION_RIGHT_PARENTHESIS, i, ')'));
                        function_parentheses--;
                        bdarray.pop_back();
                    }
                    else {
                        throw (mpe("\")\" not expected", i));
                    }
                    state = 5;
                    break;
                }
                if (e[i] == ',') {
                    if (bdarray.back().first != 0)
                        throw (mpe("Expected a \")\"", i));
                    if (bdarray.back().second-- < 2)
                        throw (mpe("Don\'t expect any arguments here", i));
                    tokens.push_back(Token(COMMA, i, ','));
                    state = 0;
                    break;
                }
                else {
                    throw (mpe((string("\"")+e[i])+"\" not expected", i));
                }
            case 6: //just read a function name
                if (e[i] == '(') {
                    state = 0;
                    break;
                }
                else {
                    throw (mpe("Expected a \"(\"", i));
                }
        }
    }
    if ((bdarray.back().first > 0) || (function_parentheses > 0)) {
        throw (mpe("Expected a \")\"", --i));
    }
    if (state != 5) {
        throw (mpe("Unexpected end of expression", --i));
    }

    //stage 2: transform expression to postfix
    deque<Token> postfix;
    vector<Token> tstack;
    while (!tokens.empty()) {
        temp = tokens.front();
        tokens.pop_front();
        switch (temp.type) {
            case INFIX_4:
            case INFIX_3:
            case INFIX_2:
                while(!tstack.empty()) {
                    int sp = tstack.back().priority;
                    if (sp < INFIX_1 || sp > temp.type) {
                        break;
                    }
                    postfix.push_back(tstack.back());
                    tstack.pop_back();
                }
            case INFIX_1:
            case LEFT_PARENTHESIS:
            case FUNCTION_NAME:
                tstack.push_back(temp);
                break;
            case UNARY:
                temp.priority = (!tstack.empty() && tstack.back().priority == INFIX_1) ?
                    INFIX_1 : INFIX_3;
                tstack.push_back(temp);
                break;
            case NUMERIC_LITERAL:
            case CONSTANT_NAME:
            case VARIABLE_NAME:
                postfix.push_back(temp);
                break;
            case RIGHT_PARENTHESIS:
                while(tstack.back().type != LEFT_PARENTHESIS) {
                    postfix.push_back(tstack.back());
                    tstack.pop_back();
                }
                tstack.pop_back();
                break;
            case FUNCTION_RIGHT_PARENTHESIS:
                do {
                    postfix.push_back(tstack.back());
                    tstack.pop_back();
                }
                while(postfix.back().type != FUNCTION_NAME);
                break;
            case COMMA:
                while(tstack.back().type != FUNCTION_NAME) {
                    postfix.push_back(tstack.back());
                    tstack.pop_back();
                }
                break;
            case FUNCTION_LEFT_PARENTHESIS:
                break;
            default:
                throw(mpe("internal error", 0));
        }
    }
    while(!tstack.empty()) {
        postfix.push_back(tstack.back());
        tstack.pop_back();
    }

    //stage 3: convert "Token" expression primitives to "Element *"

    while (!postfix.empty()) {
        temp = postfix.front();
        postfix.pop_front();
        switch (temp.type) {
            case INFIX_4:
            case INFIX_3:
            case INFIX_2:
            case INFIX_1: {
                auto name = infix_operator_to_function_name(temp.content);
                m_elist.push_back( make_function(name) );
                break;
            }
            case FUNCTION_NAME:
                m_elist.push_back(make_function(temp.content));
                break;
            case UNARY:
                if (temp.content == "-") { // unary '+' is ignored

                    // Rather than having an individual function for the unary minus
                    // we insert a zero before the last argument (which is already in
                    // the list), and use a subtraction instead.
                    // The reason is to allow the optimizer to group
                    // addition/subtraction chains. Clearly, this is a bit unorthodox
                    // and could be done in the optimizer too, but the optimizer is
                    // complex enough already.

                    link_arguments(m_elist); 
                    auto chunk = get_dependent_chunk(std::prev(m_elist.end()));
                    m_elist.insert(chunk.first, make_intermediate_constant(this, 0.0));
                    m_elist.push_back( make_function("sub") );
                }
                break;
            case NUMERIC_LITERAL: {
                double c_value = atof(temp.content.c_str());
                m_elist.push_back(make_intermediate_constant(this, c_value));
                break;
            }
            case CONSTANT_NAME: {
                m_elist.push_back(m_constants.find(temp.content)->second);
                break;
            }
            case VARIABLE_NAME: {
                auto it = m_variables.find(temp.content);
                assert(it != m_variables.end());
                it->second->referenced = true;
                m_elist.push_back(it->second);
                break;
            }
        }
    }

    // link functions to their arguments (1)
    link_arguments(m_elist);

    // choose more suitable functions, where applicable
    for (auto y = m_elist.begin(); y != m_elist.end(); ) {
        auto y_next = next(y);
        if ((*y)->element_type == CFUNC) {
            auto f = static_pointer_cast<Function>(*y);

            // eliminate constants
            if (!f->force_not_constant) {
                bool all_args_are_const = true;
                for (size_t j = 0; j < f->num_args; j++) {
                    if ((*f->args[j])->element_type != CCONST) {
                        all_args_are_const = false;
                        break;
                    }
                }
                if (all_args_are_const) {
                    elist_it_t first_arg_it = y;
                    std::advance(first_arg_it, -(int64_t)f->num_args);
                    compile_and_finalize_elist(first_arg_it, next(y));
                    double res = evaluate_fptr();
                    m_elist.erase(first_arg_it, y);
                    *y = make_intermediate_constant(this, res);
                    y = y_next;
                    continue;
                }
            }

            if (f->optimizer != 0) {
                f->optimizer(y, this, &m_elist);
            }
        }
        y = y_next;
    }

    is_constant_expression = m_elist.size()==1 && m_elist.back()->element_type == CCONST;
    if (is_constant_expression) {
        auto v = static_pointer_cast<Constant>(m_elist.back());
        constant_expression_value = v->get_data_as_double();
    }
    else {
        compile_and_finalize_elist(m_elist.begin(), m_elist.end());
    }
}



inline
void evaluator::compile_and_finalize_elist(impl::elist_it_t first, impl::elist_it_t last)
{
    using namespace impl;

    const static uint8_t return_sequence[] = {
#ifdef MEXCE_64
        // Right before the function returns, in 32-bit x86, the result is in
        // st(0), where it is expected to be. There is nothing further to do there
        // other than return.
        // In x64 however, the result is expected to be in xmm0, thus we should
        // move it there and pop the FPU stack. To achieve that, we  store the
        // result to memory and then load it to xmm0, which requires a temporary.
        // This code is used at the very end (see below), but its size must be known here.

        //  load return address to rax (last 8 bytes - address is uninitialized)
        0x48, 0xb8, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, // mov         rax, cdcdcdcdcdcdcdcdh

        // store the return value
        0xdd, 0x18,                                                 // fstp        qword ptr [rax]

        // load from the return value to xmm0
        0xf3, 0x0f, 0x7e, 0x00,                                     // movq        xmm0, mmword ptr [rax]
        0x58,                                                       // pop rax
#endif
        0xc3                                                        // return
    };

    mexce_charstream code_buffer;

#ifdef MEXCE_64
    // On x64 we are using rax to fetch/store addresses
    code_buffer < 0x50; // push rax
#endif

    compile_elist(code_buffer, first, last);

    // copy the return sequence
    code_buffer.s.write((const char*)return_sequence, sizeof(return_sequence));

    auto code = code_buffer.s.str();
    m_buffer_size = code.size();
    auto buffer = get_executable_buffer(m_buffer_size);
    memcpy(buffer, &code[0], m_buffer_size);

#ifdef MEXCE_64
    // load the intermediate variable's address to rax
    *((uint64_t*)(buffer+code.size()-16)) = (uint64_t)&m_x64_return_var;
#endif

    evaluate_fptr = lock_executable_buffer(buffer, code.size());
}

} // mexce

#endif
