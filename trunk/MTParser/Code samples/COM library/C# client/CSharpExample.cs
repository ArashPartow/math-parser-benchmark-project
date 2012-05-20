using System ;
using System.ComponentModel ;
using System.Runtime.InteropServices ;
using System.Windows.Forms ;
using MTPARSERCOMLib ;


namespace CSharpExample
{
	
	public class CSharpExample : Form
	{
		[ DllImport( "kernel32.dll" )]
		public static extern uint GetTickCount();

		#region Private Fields
		private Container components = null;
		private Button DefineMacro = null;
		private Button Index = null;
		private TextBox VarZ = null;
		private TextBox VarY = null;
		private TextBox VarX = null;
		private TextBox Result = null;
		private TextBox Msg = null;
		private Button Benchmark = null;
		private TextBox Expr = null;
		private Button Evaluate = null;
		private GroupBox Frame1 = null;
		private GroupBox Frame2 = null;
		private Label Label1 = null;
		private Label Label2 = null;
		private Label Label3 = null;
		private Label Label4 = null;

		private MacroDefinition _macroDefinition = null ;
		
		private MTParser m_parser = new MTParser();		
		private MTDouble m_x = new MTDouble();
		private MTDouble m_y = new MTDouble();
		private MTDouble m_z = new MTDouble();		

		#endregion

		public CSharpExample()
		{
			_macroDefinition = new MacroDefinition();
			InitializeComponent();

            this.AcceptButton = this.Evaluate;

			m_x.create("x", 0);
			m_y.create("y", 0);
			m_z.create("z", 0);
		}

		#region Dispose Method
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing);
		}
		#endregion

		#region Windows Form Designer generated code

		private void InitializeComponent()
		{
			this.DefineMacro = new System.Windows.Forms.Button();
			this.Index = new System.Windows.Forms.Button();
			this.VarZ = new System.Windows.Forms.TextBox();
			this.VarY = new System.Windows.Forms.TextBox();
			this.VarX = new System.Windows.Forms.TextBox();
			this.Result = new System.Windows.Forms.TextBox();
			this.Msg = new System.Windows.Forms.TextBox();
			this.Benchmark = new System.Windows.Forms.Button();
			this.Expr = new System.Windows.Forms.TextBox();
			this.Evaluate = new System.Windows.Forms.Button();
			this.Frame1 = new System.Windows.Forms.GroupBox();
			this.Frame2 = new System.Windows.Forms.GroupBox();
			this.Label1 = new System.Windows.Forms.Label();
			this.Label2 = new System.Windows.Forms.Label();
			this.Label3 = new System.Windows.Forms.Label();
			this.Label4 = new System.Windows.Forms.Label();
			this.Frame2.SuspendLayout();
			this.SuspendLayout();
			// 
			// DefineMacro
			// 
			this.DefineMacro.Location = new System.Drawing.Point(328, 208);
			this.DefineMacro.Name = "DefineMacro";
			this.DefineMacro.Size = new System.Drawing.Size(89, 25);
			this.DefineMacro.TabIndex = 15;
			this.DefineMacro.Text = "Define Macro";
			this.DefineMacro.Click += new System.EventHandler(this.DefineMacro_Click);
			// 
			// Index
			// 
			this.Index.Location = new System.Drawing.Point(328, 176);
			this.Index.Name = "Index";
			this.Index.Size = new System.Drawing.Size(89, 25);
			this.Index.TabIndex = 8;
			this.Index.Text = "Index";
			this.Index.Click += new System.EventHandler(this.Index_Click);
			// 
			// VarZ
			// 
			this.VarZ.Location = new System.Drawing.Point(56, 104);
			this.VarZ.Name = "VarZ";
			this.VarZ.Size = new System.Drawing.Size(65, 20);
			this.VarZ.TabIndex = 7;
			this.VarZ.Text = "0";
			// 
			// VarY
			// 
			this.VarY.Location = new System.Drawing.Point(56, 80);
			this.VarY.Name = "VarY";
			this.VarY.Size = new System.Drawing.Size(65, 20);
			this.VarY.TabIndex = 6;
			this.VarY.Text = "0";
			// 
			// VarX
			// 
			this.VarX.Location = new System.Drawing.Point(56, 56);
			this.VarX.Name = "VarX";
			this.VarX.Size = new System.Drawing.Size(65, 20);
			this.VarX.TabIndex = 5;
			this.VarX.Text = "0";
			// 
			// Result
			// 
			this.Result.Enabled = false;
			this.Result.Location = new System.Drawing.Point(256, 96);
			this.Result.Name = "Result";
			this.Result.ReadOnly = true;
			this.Result.Size = new System.Drawing.Size(137, 20);
			this.Result.TabIndex = 4;
			this.Result.Text = "0";
			// 
			// Msg
			// 
			this.Msg.BackColor = System.Drawing.SystemColors.Menu;
			this.Msg.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.Msg.Enabled = false;
			this.Msg.Location = new System.Drawing.Point(8, 168);
			this.Msg.Multiline = true;
			this.Msg.Name = "Msg";
			this.Msg.ReadOnly = true;
			this.Msg.Size = new System.Drawing.Size(289, 57);
			this.Msg.TabIndex = 3;
			this.Msg.Text = "";
			// 
			// Benchmark
			// 
			this.Benchmark.Location = new System.Drawing.Point(136, 104);
			this.Benchmark.Name = "Benchmark";
			this.Benchmark.Size = new System.Drawing.Size(97, 41);
			this.Benchmark.TabIndex = 2;
			this.Benchmark.Text = "Benchmark";
			this.Benchmark.Click += new System.EventHandler(this.Benchmark_Click);
			// 
			// Expr
			// 
			this.Expr.Location = new System.Drawing.Point(16, 16);
			this.Expr.Name = "Expr";
			this.Expr.Size = new System.Drawing.Size(393, 20);
			this.Expr.TabIndex = 1;
			this.Expr.Text = "pi*min(x+y+sin(z)/2^3-40.9988*2, avg(y,x*10,3,5))";
			// 
			// Evaluate
			// 
			this.Evaluate.Location = new System.Drawing.Point(136, 56);
			this.Evaluate.Name = "Evaluate";
			this.Evaluate.Size = new System.Drawing.Size(97, 41);
			this.Evaluate.TabIndex = 0;
			this.Evaluate.Text = "Evaluate";			
			this.Evaluate.Click += new System.EventHandler(this.Evaluate_Click);
			// 
			// Frame1
			// 
			this.Frame1.Location = new System.Drawing.Point(248, 72);
			this.Frame1.Name = "Frame1";
			this.Frame1.Size = new System.Drawing.Size(161, 65);
			this.Frame1.TabIndex = 10;
			this.Frame1.TabStop = false;
			this.Frame1.Text = "Result";
			// 
			// Frame2
			// 
			this.Frame2.Controls.Add(this.Label1);
			this.Frame2.Controls.Add(this.Label2);
			this.Frame2.Controls.Add(this.Label3);
			this.Frame2.Location = new System.Drawing.Point(8, 0);
			this.Frame2.Name = "Frame2";
			this.Frame2.Size = new System.Drawing.Size(409, 161);
			this.Frame2.TabIndex = 11;
			this.Frame2.TabStop = false;
			// 
			// Label1
			// 
			this.Label1.Location = new System.Drawing.Point(8, 64);
			this.Label1.Name = "Label1";
			this.Label1.Size = new System.Drawing.Size(33, 25);
			this.Label1.TabIndex = 14;
			this.Label1.Text = "X =";
			// 
			// Label2
			// 
			this.Label2.Location = new System.Drawing.Point(8, 88);
			this.Label2.Name = "Label2";
			this.Label2.Size = new System.Drawing.Size(33, 25);
			this.Label2.TabIndex = 13;
			this.Label2.Text = "Y =";
			// 
			// Label3
			// 
			this.Label3.Location = new System.Drawing.Point(8, 112);
			this.Label3.Name = "Label3";
			this.Label3.Size = new System.Drawing.Size(33, 25);
			this.Label3.TabIndex = 12;
			this.Label3.Text = "Z =";
			// 
			// Label4
			// 
			this.Label4.Location = new System.Drawing.Point(264, 80);
			this.Label4.Name = "Label4";
			this.Label4.Size = new System.Drawing.Size(73, 17);
			this.Label4.TabIndex = 9;
			this.Label4.Text = "Result:";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(426, 246);
			this.Controls.Add(this.DefineMacro);
			this.Controls.Add(this.Index);
			this.Controls.Add(this.VarZ);
			this.Controls.Add(this.VarY);
			this.Controls.Add(this.VarX);
			this.Controls.Add(this.Result);
			this.Controls.Add(this.Msg);
			this.Controls.Add(this.Benchmark);
			this.Controls.Add(this.Expr);
			this.Controls.Add(this.Evaluate);
			this.Controls.Add(this.Frame1);
			this.Controls.Add(this.Frame2);
			this.Controls.Add(this.Label4);
			this.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Location = new System.Drawing.Point(4, 30);
			this.Name = "MTParserCOMDemo";
			this.Text = "MTParserCOM: C# client demo";
			this.Load += new System.EventHandler(this.form_load);
			this.Frame2.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main()
		{
			Application.Run(new CSharpExample());
		}

		void form_load(Object _sender, EventArgs _e1) 
		{			
			try
			{				
				_macroDefinition.SetParser( m_parser ) ;

				// Define the variables and keep the keys to speed up value assignations
				m_parser.defineVar(m_x as IMTVariable);
				m_parser.defineVar(m_y as IMTVariable);
				m_parser.defineVar(m_z as IMTVariable);
				
				// Define a shared double variable for test purpose
				MTDouble v = new MTDouble();				

				v.create("v", 1.0);
				m_parser.defineVar(v as IMTVariable);
				double r = 0;
								
				r = m_parser.evaluate("v");
				
				// Change the variable's value
				v.value = 10.0;				

				r = m_parser.evaluate("v");
				Console.Out.WriteLine( "r = {0}", r ) ;

				// Create another parser and copy the existing parser configuration
				MTParser p2 = new MTParser();
				p2.copy(m_parser);

				r = p2.evaluate("v");				

				// the shared variable has been copied
				// Changing the shared variable's value updates all parsers using this variable
				v.value = 3.0;
				r = p2.evaluate("v");
				r = m_parser.evaluate("v");

				// define a constant
				m_parser.defineConst("pi", 3.14159);

                // define  a user-defined function
                m_parser.defineFunc(new MySumFunction());
				
				// Load localized information
				string dir = System.AppDomain.CurrentDomain.BaseDirectory;				
				MTParserLocalizer localizer = new MTParserLocalizer();
				localizer.locale = "en";				
				localizer.registerAllLibraries( dir, "*.xml");								
				

				sMTSyntax syntax = m_parser.getSyntax();				
				syntax.decimalPoint = '.';
				syntax.argumentSeparator = ',';
				m_parser.setSyntax(ref syntax);
				
				// Load plug-ins				
				m_parser.loadAllPlugins( dir, "*.xml");

              
                
				
				
			}
			catch ( Exception )
			{
				MessageBox.Show("Error: " + getLastExcepText(m_parser), "Project1");
			}
		}

		string getLastExcepText(MTParser parser) 
		{			
			string msg = "";
			MTExcepData e = new MTExcepData();
			MTParserLocalizer loc = new MTParserLocalizer();
			
			do
			{
				parser.getLastExcep(e);
				if (e.getID() != "ok")
				{
					string desc = "";
					try
					{
						desc = loc.getExcep(e);
					}
					catch( Exception )
					{
						// No localized description available, so take the default text
						desc = e.getDescription();
					}

					msg = msg + desc;
					msg = msg + Environment.NewLine ;
				}
			} while(e.getID() != "ok");			
			
			return msg;
		}

		void Benchmark_Click(Object _sender, EventArgs _e1) 
		{		
			
			try
			{
				// For optimum performance evaluate in a batch...

				// Redefine vector variables to contain multiple values 
				MTParser benchParser = new MTParser();
				benchParser.copy( m_parser );
				
				MTDoubleVector x = new MTDoubleVector();
				MTDoubleVector y = new MTDoubleVector();
				MTDoubleVector z = new MTDoubleVector();
				x.create("x");
				y.create("y");
				z.create("z");
                
				benchParser.undefineAllVars();
				benchParser.defineVar(x as IMTVariable);
				benchParser.defineVar(y as IMTVariable);
				benchParser.defineVar(z as IMTVariable);			

				// Compile the expression only once
				benchParser.compile(Expr.Text);				
				
				// Generate random variable values...
				int nbEvals = 400000;				

				double[] xval = new double[nbEvals];
				double[] yval = new double[nbEvals];
				double[] zval = new double[nbEvals];
				System.Random r = new System.Random(100);

				for(int i = 0; i < nbEvals; i += 1)
				{					
					xval[i] = r.Next(0, 1000);
					yval[i] = r.Next(0, 1000);
					zval[i] = r.Next(0, 1000);
				}
				
				// Set values...				
				x.setValueVector(xval);
				y.setValueVector(yval);
				z.setValueVector(zval);				
				
				
				double[] results = new double[nbEvals];		// this will contain all the results after evaluations
				
				long beginTime = 0;
				long endTime = 0;				
				beginTime = GetTickCount();								// start the timer
				benchParser.evaluateCompiledBatch(nbEvals, results);	// do all evaluations in one call, avoiding multiple COM calls							
				endTime = GetTickCount();								// stop the timer

				long elapsedTime = 0;
				elapsedTime = endTime - beginTime;				

				long nbEvalSec = 0;
				double timePerEval = 0;
				timePerEval = elapsedTime / (double)nbEvals;
				nbEvalSec = (long)(nbEvals / elapsedTime * 1000.0);

				Msg.Text = "Nb. Evaluations: " + nbEvals;
				Msg.Text = Msg.Text + Environment.NewLine ;
				Msg.Text = Msg.Text + "Elapsed time (ms): " + elapsedTime;
				Msg.Text = Msg.Text + Environment.NewLine ;
				Msg.Text = Msg.Text + "Time per evaluation (ms): " + timePerEval;
				Msg.Text = Msg.Text + Environment.NewLine ;
				Msg.Text = Msg.Text + "Nb. Eval per sec: " + nbEvalSec;
			}
			catch ( Exception e)
			{
				Msg.Text = "Error: " + e.Message;
			}
		}

		void Evaluate_Click(Object _sender, EventArgs _e1) 
		{
			try
			{
				// Update the variable' values
				m_x.setValue(Convert.ToDouble(VarX.Text));
				m_y.setValue(Convert.ToDouble(VarY.Text));
				m_z.setValue(Convert.ToDouble(VarZ.Text));
				
				// Evaluate the expression with the current variable' values
				Result.Text = Convert.ToString(m_parser.evaluate(Expr.Text));

				// Print the used variables
				int nbUsedVars = 0;
				nbUsedVars = m_parser.getNbUsedVars();
				
				Msg.Text = "Used variables: ";
				string symbol;
				for(int t = 0; t <= nbUsedVars - 1; t += 1)
				{
					symbol = m_parser.getUsedVar(t);
					Msg.Text = Msg.Text + symbol;
					if (t != nbUsedVars - 1)
					{
						Msg.Text = Msg.Text + ", ";
					}
				}
			}
			catch ( Exception )
			{
				Msg.Text = "Syntax error: " + getLastExcepText(m_parser);
			}
		}

		void Index_Click(Object _sender, EventArgs _e1) 
		{
			IndexDlg frm = new IndexDlg();
			frm.SetParser( m_parser );
			frm.ShowDialog( this ) ;
		}

		void DefineMacro_Click(Object _sender, EventArgs _e1) 
		{
			_macroDefinition.ShowDialog( this ) ;
		}

		
	}


    /// <summary>
    /// Example of a user-defined function.  Implement only
    /// the evaluateX method specified by the getNbArgs method.
    /// </summary>
public class MySumFunction : IMTFunction
{
    public double evaluate0()
    {            
        throw new Exception("The method or operation is not implemented.");
    }

    public double evaluate1(double arg)
    {
        return arg;
    }

    public double evaluate2(double arg, double arg2)
    {
        return arg + arg2;
    }

    public double evaluate3(double arg, double arg2, double arg3)
    {
        return arg + arg2 + arg3;
    }

    public double evaluate(Array pArgs)
    {
        double sum = 0;
        for (int t = 0; t < pArgs.Length; t++)
        {
            sum += (double)pArgs.GetValue(t);
        }

        return sum;
    }

    public string getDescription()
    {
        return "Computes the sum of many values";
    }

    public string getHelpString()
    {
        return "slowsum(x,y,z,...)";
    }

    public int getNbArgs()
    {
        return -1;
    }

    public string getSymbol()
    {
        return "slowsum";
    }
}

}
