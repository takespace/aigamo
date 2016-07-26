using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

// 空白ページのアイテム テンプレートについては、http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 を参照してください

namespace AigamoControl
{
    /// <summary>
    /// それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private SerialDevice _SerialPort;

        public MainPage()
        {
            this.InitializeComponent();
        }

        private async void Page_Loaded(object sender, RoutedEventArgs e)
        {
            // 画質が落ちるのを防ぐ措置
            var bitmapSignal = ImageSignal.Source as BitmapImage;
            bitmapSignal.DecodePixelWidth = 477;
            bitmapSignal.DecodePixelHeight = 164;

            string aqs = SerialDevice.GetDeviceSelectorFromUsbVidPid(0x2A03, 0x0043);   // Arduino Uno R3
            //string aqs = SerialDevice.GetDeviceSelectorFromUsbVidPid(0x0403, 0x6001);   // TTL-232R-5V
            var dis = await DeviceInformation.FindAllAsync(aqs);
            if (dis.Count <= 0) return;

            _SerialPort = await SerialDevice.FromIdAsync(dis[0].Id);
            _SerialPort.BaudRate = 9600;
            _SerialPort.DataBits = 8;
            _SerialPort.Parity = SerialParity.None;
            _SerialPort.StopBits = SerialStopBitCount.One;
            _SerialPort.Handshake = SerialHandshake.None;
            _SerialPort.WriteTimeout = TimeSpan.FromMilliseconds(1000);
            _SerialPort.ReadTimeout = TimeSpan.FromMilliseconds(1000);

            StoryboardFeet.Begin();
            Storyboard1.Begin();
        }

        private void Page_Unloaded(object sender, RoutedEventArgs e)
        {
            _SerialPort?.Dispose();
        }

        private async void ForwardLeft_Click(object sender, RoutedEventArgs e)
        {
            var writer = new DataWriter(_SerialPort.OutputStream);
            writer.WriteBytes(new byte[] { 0, });
            await writer.StoreAsync();
        }

        private async void ForwardRight_Click(object sender, RoutedEventArgs e)
        {
            var writer = new DataWriter(_SerialPort.OutputStream);
            writer.WriteBytes(new byte[] { 1, });
            await writer.StoreAsync();
        }

        private void StopLeft_Click(object sender, RoutedEventArgs e)
        {
        }

        private void StopRight_Click(object sender, RoutedEventArgs e)
        {
        }

        private void BackwordLeft_Click(object sender, RoutedEventArgs e)
        {
        }

        private void BackwordRight_Click(object sender, RoutedEventArgs e)
        {
        }
    }
}
