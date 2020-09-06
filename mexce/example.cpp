#include <iostream>
#include "mexce.h"

int main()
{
    using std::cout;
    using std::endl;

    short   x0 = 0;
    float   x  = 0.0f;
    double  y  = 0.1;
    int     z  = 200;
    
    mexce::evaluator eval;

    eval.bind(x0, "x");
    eval.bind(y, "y");
    eval.bind(z, "z");

    // binding a variable as "log" will fail, as there is a function called "log"
    cout << endl << "Attempting to bind 'x' as 'log'" << endl;
    try {
        eval.bind(x, "log");
    }
    catch (std::exception& e) {
        cout << "  " << e.what() << endl;
    }

    // binding a variable as "pi" will fail, as there is a built-in constant called "pi"
    cout << endl << "Attempting to bind 'x' as 'pi'" << endl;
    try {
        eval.bind(x, "pi");
    }
    catch (std::exception& e) {
        cout << "  " << e.what() << endl;
    }

    // replaces previous binding of variable x0 to "x"
    eval.bind(x, "x");

    eval.assign_expression("0.3+(-sin(2.33+x-logb((.3*pi+(88/y)/e),3.2+z)))/98");
    
    cout << endl << "Evaluation results:" << endl;
    for (int i = 0; i < 10; i++, x-=0.1f, y+=0.212, z+=2) {
        cout << "  " << eval.evaluate() << endl; // evaluation will use bound variables x, y and z
    }

    // attempting to unbind an unknown variable, will throw an exception
    cout << endl << "Attempting to unbind w" << endl;
    try {
        eval.unbind("w");
    }
    catch (std::exception& e) {
        cout << "  " << e.what() << endl;
    }
    
    // Releasing a bound variable which is contained in the assigned expression will
    // invalidate the expression.
    cout << endl << "Unbinding x" << endl;
    eval.unbind("x");

    cout << endl << "Evaluation result:" << endl;
    cout << "  " << eval.evaluate() << endl; // Now it will return 0

    return 0;
}
