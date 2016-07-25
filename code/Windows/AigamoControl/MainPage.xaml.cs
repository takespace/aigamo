using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// 空白ページのアイテム テンプレートについては、http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 を参照してください

namespace AigamoControl
{
    /// <summary>
    /// それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            StoryboardFeet.Begin();
        }

        private void ForwardLeft_Click(object sender, RoutedEventArgs e)
        {
        }

        private void ForwardRight_Click(object sender, RoutedEventArgs e)
        {
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
