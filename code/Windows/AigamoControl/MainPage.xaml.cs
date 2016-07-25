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
using Milkcocoa;

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

        private Milkcocoa.Milkcocoa milkcocoa;
        private Milkcocoa.DataStore dataStore;

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            milkcocoa = new Milkcocoa.Milkcocoa("iceinixlzq3.mlkcca.com");
            dataStore = milkcocoa.dataStore("aigamo");
        }

        private void ForwardLeft_Click(object sender, RoutedEventArgs e)
        {
            milkcocoa.dataStore("aigamo").send(new { motor = "L", on = 1, speed = (int)slider.Value, });
        }

        private void ForwardRight_Click(object sender, RoutedEventArgs e)
        {
            milkcocoa.dataStore("aigamo").send(new { motor = "R", on = 1, speed = (int)slider.Value, });
        }

        private void StopLeft_Click(object sender, RoutedEventArgs e)
        {
            milkcocoa.dataStore("aigamo").send(new { motor = "L", on = 0, speed = (int)slider.Value, });
        }

        private void StopRight_Click(object sender, RoutedEventArgs e)
        {
            milkcocoa.dataStore("aigamo").send(new { motor = "R", on = 0, speed = (int)slider.Value, });
        }

        private void BackwordLeft_Click(object sender, RoutedEventArgs e)
        {
            milkcocoa.dataStore("aigamo").send(new { motor = "L", on = -1, speed = (int)slider.Value, });
        }

        private void BackwordRight_Click(object sender, RoutedEventArgs e)
        {
            milkcocoa.dataStore("aigamo").send(new { motor = "R", on = -1, speed = (int)slider.Value, });
        }

    }
}
