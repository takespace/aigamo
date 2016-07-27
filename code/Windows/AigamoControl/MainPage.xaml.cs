using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

// 空白ページのアイテム テンプレートについては、http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 を参照してください

namespace AigamoControl
{
    /// <summary>
    /// それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private ArduinoDevice _Arduino;

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

            var dis = await ArduinoDevice.GetDeviceInformationsFromUsbVidPidAsync(ArduinoDevice.INTERFACE_ARDUINO_UNO_R3);
            if (dis.Count <= 0) return;

            _Arduino = await ArduinoDevice.FromIdAsync(dis[0].Id);

            StoryboardFeet.Begin();
            Storyboard1.Begin();
        }

        private void Page_Unloaded(object sender, RoutedEventArgs e)
        {
            _Arduino?.Dispose();
        }

        private async void ForwardLeft_Click(object sender, RoutedEventArgs e)
        {
            await _Arduino.Write(new byte[] { 0, });
        }

        private async void ForwardRight_Click(object sender, RoutedEventArgs e)
        {
            await _Arduino.Write(new byte[] { 1, });
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
