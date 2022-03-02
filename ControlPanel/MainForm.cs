



using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace ControlPanel
{
    public partial class MainForm : Form
    {
        
        public MainForm()
        {
            InitializeComponent();
        }

        private void StopServer(object sender, EventArgs e)
        {
            try
            {
                //Server Stopping Code
                this.lblStatus.Text = "Server is Stopped";

            }
            catch(Exception ex)
            {
        
            }
        }

        private void OnStartFromContextMenu(object sender, EventArgs e)
        {

        }

        private void OnExpandFromContextMenu(object sender, EventArgs e)
        {

        }

        private void MainForm_Move(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.Hide();
                notifyIcon.ShowBalloonTip(1000, "MouseRemote","MouseRemote is Minimized to system tray! dont worry you can still use its service.",ToolTipIcon.Info);
            }
        }

        private void OnExitFromContextMenu(object sender, EventArgs e)
        {

        }

        private void OnStopFromContextMenu(object sender, EventArgs e)
        {

        }

        private void OnShowFromContextMenu(object sender, EventArgs e)
        {
            this.Show();
            this.WindowState = FormWindowState.Normal;

        }

        private void OnKeyboardFromContextMenu(object sender, EventArgs e)
        {

        }

        private void OnGamePadFromConextMenu(object sender, EventArgs e)
        {

        }

        private void StartServer(object sender, EventArgs e)
        {

            try
            {
                //Server Starting Code
                this.lblStatus.Text = "Server is Running";
            }
            catch (Exception ex)
            {
                this.lblStatus.Text = "Server is Failed to Start";

            }


        }

        private void notufyIconOnClick(object sender, MouseEventArgs e)
        {
           
        }


        []
        string Start();
        string Stop();
    }
}
