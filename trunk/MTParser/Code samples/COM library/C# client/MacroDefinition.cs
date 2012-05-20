using System ;
using System.ComponentModel ;
using System.Windows.Forms ;
using MTPARSERCOMLib ;

namespace CSharpExample
{
	public class MacroDefinition : Form
	{
		private Container components = null;
		private GroupBox Frame1 = null;
		private TextBox MacroFunction = null;
		private Button DefineMacro = null;
		private TextBox MacroDescription = null;
		private TextBox MacroSymbol = null;
		private Label Label4 = null;
		private Label Label3 = null;
		private Label Label2 = null;
		private Label Label1 = null;

		public MacroDefinition()
		{
			InitializeComponent();
		}

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

		#region Windows Form Designer generated code

		private void InitializeComponent()
		{
			this.Frame1 = new System.Windows.Forms.GroupBox();
			this.MacroFunction = new System.Windows.Forms.TextBox();
			this.DefineMacro = new System.Windows.Forms.Button();
			this.MacroDescription = new System.Windows.Forms.TextBox();
			this.MacroSymbol = new System.Windows.Forms.TextBox();
			this.Label4 = new System.Windows.Forms.Label();
			this.Label3 = new System.Windows.Forms.Label();
			this.Label2 = new System.Windows.Forms.Label();
			this.Label1 = new System.Windows.Forms.Label();
			this.Frame1.SuspendLayout();
			this.SuspendLayout();
			// 
			// Frame1
			// 
			this.Frame1.Controls.Add(this.MacroFunction);
			this.Frame1.Controls.Add(this.DefineMacro);
			this.Frame1.Controls.Add(this.MacroDescription);
			this.Frame1.Controls.Add(this.MacroSymbol);
			this.Frame1.Controls.Add(this.Label4);
			this.Frame1.Controls.Add(this.Label3);
			this.Frame1.Controls.Add(this.Label2);
			this.Frame1.Controls.Add(this.Label1);
			this.Frame1.Location = new System.Drawing.Point(16, 16);
			this.Frame1.Name = "Frame1";
			this.Frame1.Size = new System.Drawing.Size(529, 185);
			this.Frame1.TabIndex = 0;
			this.Frame1.TabStop = false;
			this.Frame1.Text = "Macro";
			// 
			// MacroFunction
			// 
			this.MacroFunction.Location = new System.Drawing.Point(152, 48);
			this.MacroFunction.Name = "MacroFunction";
			this.MacroFunction.Size = new System.Drawing.Size(353, 20);
			this.MacroFunction.TabIndex = 8;
			this.MacroFunction.Text = "";
			// 
			// DefineMacro
			// 
			this.DefineMacro.Location = new System.Drawing.Point(400, 144);
			this.DefineMacro.Name = "DefineMacro";
			this.DefineMacro.Size = new System.Drawing.Size(97, 25);
			this.DefineMacro.TabIndex = 7;
			this.DefineMacro.Text = "Define";
			this.DefineMacro.Click += new System.EventHandler(this.DefineMacro_Click);
			// 
			// MacroDescription
			// 
			this.MacroDescription.Location = new System.Drawing.Point(24, 104);
			this.MacroDescription.Name = "MacroDescription";
			this.MacroDescription.Size = new System.Drawing.Size(481, 20);
			this.MacroDescription.TabIndex = 6;
			this.MacroDescription.Text = "";
			// 
			// MacroSymbol
			// 
			this.MacroSymbol.Location = new System.Drawing.Point(24, 48);
			this.MacroSymbol.Name = "MacroSymbol";
			this.MacroSymbol.Size = new System.Drawing.Size(97, 20);
			this.MacroSymbol.TabIndex = 4;
			this.MacroSymbol.Text = "";
			// 
			// Label4
			// 
			this.Label4.Location = new System.Drawing.Point(24, 88);
			this.Label4.Name = "Label4";
			this.Label4.Size = new System.Drawing.Size(129, 17);
			this.Label4.TabIndex = 5;
			this.Label4.Text = "Macro\'s description";
			// 
			// Label3
			// 
			this.Label3.Location = new System.Drawing.Point(152, 32);
			this.Label3.Name = "Label3";
			this.Label3.Size = new System.Drawing.Size(137, 17);
			this.Label3.TabIndex = 3;
			this.Label3.Text = "Macro\'s function";
			// 
			// Label2
			// 
			this.Label2.Location = new System.Drawing.Point(128, 48);
			this.Label2.Name = "Label2";
			this.Label2.Size = new System.Drawing.Size(17, 33);
			this.Label2.TabIndex = 2;
			this.Label2.Text = "=";
			this.Label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// Label1
			// 
			this.Label1.Location = new System.Drawing.Point(24, 32);
			this.Label1.Name = "Label1";
			this.Label1.Size = new System.Drawing.Size(81, 17);
			this.Label1.TabIndex = 1;
			this.Label1.Text = "Macro\' symbol";
			// 
			// MacroDefinition
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(559, 224);
			this.Controls.Add(this.Frame1);
			this.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Location = new System.Drawing.Point(4, 30);
			this.Name = "MacroDefinition";
			this.Text = "Macro Definition";
			this.Frame1.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		MTParser m_parser = null;
		void DefineMacro_Click(Object _sender, EventArgs _e1) 
		{
			// WARNING: On Error GOTO define_error  is not supported
			try
			{
				m_parser.defineMacro(MacroSymbol.Text, MacroFunction.Text, MacroDescription.Text);
				MessageBox.Show("New macro defined: " + MacroSymbol.Text, "Project1");
			}
			catch ( Exception e )
			{
				MessageBox.Show("Error defining the macro: " + e.ToString(), "Project1");
			}
		}

		public void SetParser(MTParser parser) 
		{
			m_parser = parser;
		}
	}
}
