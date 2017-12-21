using SAPI;
using SAPI.Overlay;
using System.Threading;

namespace Example
{
    class Program
    {
        private static void Main(string[] args)
        {
            // SAMP is open
            GeneralAPI.Instance.Initialize();

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
