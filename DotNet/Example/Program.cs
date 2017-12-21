using SAPI;
using SAPI.Overlay;
using System.Threading;

namespace Example
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            // SAMP is open
            int result = GeneralAPI.Instance.Initialize();

            int id = GeneralAPI.Instance.GetWeatherID();

            Thread.Sleep(500);

            ChatAPI.Instance.Send("Hello");

            var textID = TextAPI.Instance.Create();
            TextAPI.Instance.SetActive(textID, true);
            TextAPI.Instance.SetText(textID, "Hello");

            while (true)
                Thread.Sleep(500);

            // SAMP is closed
            // GeneralAPI.Instance.ResetInitialize();
        }
    }
}