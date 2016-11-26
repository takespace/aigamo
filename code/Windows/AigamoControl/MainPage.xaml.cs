using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
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

            ForwardButton.AddHandler(PointerPressedEvent, new PointerEventHandler(ForwardButton_PointerPressed), true);
            ForwardButton.AddHandler(PointerReleasedEvent, new PointerEventHandler(Button_PointerReleased), true);
            BackwardButton.AddHandler(PointerPressedEvent, new PointerEventHandler(BackwardButton_PointerPressed), true);
            BackwardButton.AddHandler(PointerReleasedEvent, new PointerEventHandler(Button_PointerReleased), true);
            LeftButton.AddHandler(PointerPressedEvent, new PointerEventHandler(LeftButton_PointerPressed), true);
            LeftButton.AddHandler(PointerReleasedEvent, new PointerEventHandler(Button_PointerReleased), true);
            RightButton.AddHandler(PointerPressedEvent, new PointerEventHandler(RightButton_PointerPressed), true);
            RightButton.AddHandler(PointerReleasedEvent, new PointerEventHandler(Button_PointerReleased), true);
            TurnCwButton.AddHandler(PointerPressedEvent, new PointerEventHandler(TurnCwButton_PointerPressed), true);
            TurnCwButton.AddHandler(PointerReleasedEvent, new PointerEventHandler(Button_PointerReleased), true);
            TurnCcwButton.AddHandler(PointerPressedEvent, new PointerEventHandler(TurnCcwButton_PointerPressed), true);
            TurnCcwButton.AddHandler(PointerReleasedEvent, new PointerEventHandler(Button_PointerReleased), true);

            var dis = await ArduinoDevice.GetDeviceInformationsFromUsbVidPidAsync(ArduinoDevice.INTERFACE_ARDUINO_UNO_R3TAKE);
            if (dis.Count <= 0) return;

            _Arduino = await ArduinoDevice.FromIdAsync(dis[0].Id);

            StoryboardAntena.Begin();
        }

        private void Page_Unloaded(object sender, RoutedEventArgs e)
        {
            _Arduino?.Dispose();
        }

        private void ForwardButton_PointerPressed(object sender, PointerRoutedEventArgs e)
        {
            ChangeFeetSpeed(slider.Value);
            _Arduino?.Write('F', (byte)(slider.Value * 100));
        }

        private void BackwardButton_PointerPressed(object sender, PointerRoutedEventArgs e)
        {
            ChangeFeetSpeed(-slider.Value);
            _Arduino?.Write('B', (byte)(slider.Value * 100));
        }

        private void LeftButton_PointerPressed(object sender, PointerRoutedEventArgs e)
        {
            _Arduino?.Write('L', 0);
        }

        private void RightButton_PointerPressed(object sender, PointerRoutedEventArgs e)
        {
            _Arduino?.Write('R', 0);
        }

        private void TurnCwButton_PointerPressed(object sender, PointerRoutedEventArgs e)
        {
            _Arduino?.Write('c', 0);
        }

        private void TurnCcwButton_PointerPressed(object sender, PointerRoutedEventArgs e)
        {
            _Arduino?.Write('C', 0);
        }

        private void Button_PointerReleased(object sender, Windows.UI.Xaml.Input.PointerRoutedEventArgs e)
        {
            ChangeFeetSpeed(0);
            _Arduino?.Write('S', 0);
        }

        private enum FeetSpeedType
        {
            Stop,
            ForwardFast,
            ForwardSlow,
            BackwardFast,
            BackwardSlow,
        }

        private FeetSpeedType __FeetSpeed = FeetSpeedType.Stop;
        private FeetSpeedType _FeetSpeed
        {
            get
            {
                return __FeetSpeed;
            }
            set
            {
                if (__FeetSpeed == value) return;

                if (value == FeetSpeedType.Stop)
                {
                    StoryboardFeet.Stop();
                }
                else
                {
                    StoryboardFeet.Stop();
                    switch (value)
                    {
                        case FeetSpeedType.ForwardFast:
                            AnimationFootFront.To = -360;
                            AnimationFootFront.Duration = new Duration(new System.TimeSpan(0, 0, 0, 1));
                            AnimationFootRear.To = -360;
                            AnimationFootRear.Duration = new Duration(new System.TimeSpan(0, 0, 0, 1));
                            break;
                        case FeetSpeedType.ForwardSlow:
                            AnimationFootFront.To = -360;
                            AnimationFootFront.Duration = new Duration(new System.TimeSpan(0, 0, 0, 3));
                            AnimationFootRear.To = -360;
                            AnimationFootRear.Duration = new Duration(new System.TimeSpan(0, 0, 0, 3));
                            break;
                        case FeetSpeedType.BackwardFast:
                            AnimationFootFront.To = 360;
                            AnimationFootFront.Duration = new Duration(new System.TimeSpan(0, 0, 0, 1));
                            AnimationFootRear.To = 360;
                            AnimationFootRear.Duration = new Duration(new System.TimeSpan(0, 0, 0, 1));
                            break;
                        case FeetSpeedType.BackwardSlow:
                            AnimationFootFront.To = 360;
                            AnimationFootFront.Duration = new Duration(new System.TimeSpan(0, 0, 0, 3));
                            AnimationFootRear.To = 360;
                            AnimationFootRear.Duration = new Duration(new System.TimeSpan(0, 0, 0, 3));
                            break;
                    }
                    StoryboardFeet.Begin();
                }

                __FeetSpeed = value;
            }
        }

        private void ChangeFeetSpeed(double speed)
        {
            if (speed == 0)
            {
                _FeetSpeed = FeetSpeedType.Stop;
            }
            else if (speed > 0.5)
            {
                _FeetSpeed = FeetSpeedType.ForwardFast;
            }
            else if (speed > 0)
            {
                _FeetSpeed = FeetSpeedType.ForwardSlow;
            }
            else if (speed < -0.5)
            {
                _FeetSpeed = FeetSpeedType.BackwardFast;
            }
            else
            {
                _FeetSpeed = FeetSpeedType.BackwardSlow;
            }
        }
    }
}
