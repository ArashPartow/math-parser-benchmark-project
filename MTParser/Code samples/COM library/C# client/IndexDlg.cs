using System ;
using System.ComponentModel ;
using System.Windows.Forms ;
using MTPARSERCOMLib ;

namespace CSharpExample
{
	public class IndexDlg : Form
	{
		private Container components = null;
		private Button Ok = null;
		private GroupBox Frame2 = null;
		private ListBox Constants = null;
		private GroupBox DefinedFuncs = null;
		private ListBox Functions = null;
		private GroupBox Frame1 = null;
		private ListBox Operators = null;

		public IndexDlg()
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
			this.Ok = new System.Windows.Forms.Button();
			this.Frame2 = new System.Windows.Forms.GroupBox();
			this.Constants = new System.Windows.Forms.ListBox();
			this.DefinedFuncs = new System.Windows.Forms.GroupBox();
			this.Functions = new System.Windows.Forms.ListBox();
			this.Frame1 = new System.Windows.Forms.GroupBox();
			this.Operators = new System.Windows.Forms.ListBox();
			this.Frame2.SuspendLayout();
			this.DefinedFuncs.SuspendLayout();
			this.Frame1.SuspendLayout();
			this.SuspendLayout();
			// 
			// Ok
			// 
			this.Ok.Location = new System.Drawing.Point(440, 440);
			this.Ok.Name = "Ok";
			this.Ok.Size = new System.Drawing.Size(73, 25);
			this.Ok.TabIndex = 6;
			this.Ok.Text = "Ok";
			this.Ok.Click += new System.EventHandler(this.Ok_Click);
			// 
			// Frame2
			// 
			this.Frame2.Controls.Add(this.Constants);
			this.Frame2.Location = new System.Drawing.Point(16, 320);
			this.Frame2.Name = "Frame2";
			this.Frame2.Size = new System.Drawing.Size(673, 105);
			this.Frame2.TabIndex = 4;
			this.Frame2.TabStop = false;
			this.Frame2.Text = "Defined Constants";
			// 
			// Constants
			// 
			this.Constants.ItemHeight = 14;
			this.Constants.Location = new System.Drawing.Point(8, 24);
			this.Constants.Name = "Constants";
			this.Constants.Size = new System.Drawing.Size(657, 60);
			this.Constants.Sorted = true;
			this.Constants.TabIndex = 5;
			// 
			// DefinedFuncs
			// 
			this.DefinedFuncs.Controls.Add(this.Functions);
			this.DefinedFuncs.Location = new System.Drawing.Point(16, 128);
			this.DefinedFuncs.Name = "DefinedFuncs";
			this.DefinedFuncs.Size = new System.Drawing.Size(673, 185);
			this.DefinedFuncs.TabIndex = 2;
			this.DefinedFuncs.TabStop = false;
			this.DefinedFuncs.Text = "Defined Functions";
			// 
			// Functions
			// 
			this.Functions.ItemHeight = 14;
			this.Functions.Location = new System.Drawing.Point(8, 24);
			this.Functions.Name = "Functions";
			this.Functions.Size = new System.Drawing.Size(657, 130);
			this.Functions.Sorted = true;
			this.Functions.TabIndex = 3;
			// 
			// Frame1
			// 
			this.Frame1.Controls.Add(this.Operators);
			this.Frame1.Location = new System.Drawing.Point(16, 8);
			this.Frame1.Name = "Frame1";
			this.Frame1.Size = new System.Drawing.Size(673, 113);
			this.Frame1.TabIndex = 0;
			this.Frame1.TabStop = false;
			this.Frame1.Text = "Defined Operators";
			// 
			// Operators
			// 
			this.Operators.ItemHeight = 14;
			this.Operators.Location = new System.Drawing.Point(8, 24);
			this.Operators.Name = "Operators";
			this.Operators.Size = new System.Drawing.Size(657, 60);
			this.Operators.Sorted = true;
			this.Operators.TabIndex = 1;
			// 
			// IndexDlg
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(703, 479);
			this.Controls.Add(this.Ok);
			this.Controls.Add(this.Frame2);
			this.Controls.Add(this.DefinedFuncs);
			this.Controls.Add(this.Frame1);
			this.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Location = new System.Drawing.Point(4, 30);
			this.Name = "IndexDlg";
			this.Text = "Operator, function and constant index";
			this.Load += new System.EventHandler(this.form_load);
			this.Frame2.ResumeLayout(false);
			this.DefinedFuncs.ResumeLayout(false);
			this.Frame1.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		MTParser m_parser = null;
		public void SetParser(MTParser parser) 
		{
			m_parser = parser;
		}

		void form_load(Object _sender, EventArgs _e1) 
		{
			string str = String.Empty;
			sMTOperator opInfo = new sMTOperator();
			sMTFunction funcInfo = new sMTFunction();
			sMTConstant constInfo = new sMTConstant();
			int nbOps = 0;
			int t = 0;
			int nbFuncs = 0;
			int nbConsts = 0;
			MTParserLocalizer loc = new MTParserLocalizer();
			sMTSyntax syntax = m_parser.getSyntax();			
			
			nbOps = m_parser.getNbDefinedOps();
			for(t = 0; t <= nbOps - 1; t += 1)
			{
				opInfo = m_parser.getOp(t);
				try
				{
					opInfo = loc.getOpInfo(opInfo.ID);
				}
				catch( Exception ){}

				str = opInfo.symbol + (char)(9) + opInfo.helpString + (char)(9) + opInfo.description;
					Operators.Items.Add(str);
			}
			nbFuncs = m_parser.getNbDefinedFuncs();
			for(t = 0; t <= nbFuncs - 1; t += 1)
			{
				funcInfo = m_parser.getFunc(t);
				try
				{
					funcInfo = loc.getFuncInfo(funcInfo.ID, ref syntax);
				}
				catch( Exception ){}

				str = funcInfo.symbol + (char)(9) + funcInfo.helpString + (char)(9) + funcInfo.description;
					Functions.Items.Add(str);
			}
			nbConsts = m_parser.getNbDefinedConsts();
			for(t = 0; t <= nbConsts - 1; t += 1)
			{
				constInfo = m_parser.getConst(t);				
				str = constInfo.name + (char)(9) + constInfo.value;
					Constants.Items.Add(str);
			}
		}

		void Ok_Click(Object _sender, EventArgs _e1) 
		{
			this.Close();
			//this.Hide();
		}


	}


}
