using System;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;
using Windows.Storage.Streams;

namespace AigamoControl
{
    class ArduinoDevice : IDisposable
    {
        public static ushort[] INTERFACE_ARDUINO_UNO_R3 { get { return new ushort[] { 0x2A03, 0x0043 }; } }
        public static readonly ushort[] INTERFACE_TTL232R5V = new ushort[] { 0x0403, 0x6001 };

        private SerialDevice _Device;
        private DataWriter _DeviceWriter;
        private DataReader _DeviceReader;

        public static async Task<DeviceInformationCollection> GetDeviceInformationsFromUsbVidPidAsync(ushort[] vidPid)
        {
            string aqs = SerialDevice.GetDeviceSelectorFromUsbVidPid(vidPid[0], vidPid[1]);
            return await DeviceInformation.FindAllAsync(aqs);
        }

        public static async Task<ArduinoDevice> FromIdAsync(string deviceId)
        {
            return new ArduinoDevice(await SerialDevice.FromIdAsync(deviceId));
        }

        private ArduinoDevice(SerialDevice device)
        {
            _Device = device;

            _Device.BaudRate = 9600;
            _Device.DataBits = 8;
            _Device.Parity = SerialParity.None;
            _Device.StopBits = SerialStopBitCount.One;
            _Device.Handshake = SerialHandshake.None;
            _Device.WriteTimeout = TimeSpan.FromMilliseconds(1000);
            _Device.ReadTimeout = TimeSpan.FromMilliseconds(1000);

            _DeviceWriter = new DataWriter(_Device.OutputStream);
            _DeviceReader = new DataReader(_Device.InputStream);
            _DeviceReader.InputStreamOptions = InputStreamOptions.Partial;
        }

        public void Dispose()
        {
            _Device?.Dispose();
            _Device = null;
        }

        public async Task Write(byte[] value)
        {
            _DeviceWriter.WriteBytes(value);
            await _DeviceWriter.StoreAsync();
        }

        public async Task<byte[]> Read()
        {
            uint bytesRead;
            do
            {
                bytesRead = await _DeviceReader.LoadAsync(1024);
            }
            while (bytesRead <= 0);

            var value = new byte[bytesRead];
            _DeviceReader.ReadBytes(value);

            return value;
        }

    }
}
