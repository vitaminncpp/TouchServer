



using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace ControlPanel
{
    public partial class MainForm : Form
    {

        private System.Diagnostics.Process run;
        private bool running = false;

        /**
        [DllImport("ServiceDll.Dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Start();

        [DllImport("ServiceDll.Dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Stop();

        */

        public MainForm()
        {
            InitializeComponent();
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
            if (!running)
            {
                try
                {
                    run = Process.Start("MouseRemote.exe");
                    this.lblStatus.Text = "Server is Running";
                    running = true;

                }
                catch (Exception ex)
                {
                    this.lblStatus.Text = "Failed to Start:" + ex.ToString();

                }
            }
           
        }
        private void StopServer(object sender, EventArgs e)
        {
            if (running)
            {
                try
                {
                    run.Kill();
                    this.lblStatus.Text = "Server is NOT Running";
                    running = false;

                }
                catch (Exception ex)
                {
                    this.lblStatus.Text = "Failed to Stop:" + ex.ToString();
                }
            }
           
        }


        private void notufyIconOnClick(object sender, MouseEventArgs e)
        {
           
        }

        private void OnExit(object sender, FormClosedEventArgs e)
        {
            if (running)
            {
                run.Kill();
            }
        }
    }
}
