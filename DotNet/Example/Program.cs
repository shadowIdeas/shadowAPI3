using SAPI;
using SAPI.Overlay;
using System;
using System.Threading;

namespace Example
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            // SAMP is open
            int result = GeneralAPI.Instance.Initialize();

            var d = DialogAPI.Instance;
            var c = ChatAPI.Instance;
            var p = PlayerAPI.Instance;
            var v = VehicleAPI.Instance;
            var b = BoxAPI.Instance;
            var t = TextAPI.Instance;

            var ps = SAPI.SAMP.PlayerAPI.Instance;
            var vs = SAPI.SAMP.VehicleAPI.Instance;

            Thread.Sleep(500);

            ChatAPI.Instance.Send("Hello");

            var textID = TextAPI.Instance.Create();
            TextAPI.Instance.SetActive(textID, true);
            TextAPI.Instance.SetText(textID, "Hello");

            while (true)
            {
                Console.Clear();
                Console.WriteLine($"Health: {p.GetHealth()}\tArmor: {p.GetArmor()}");
                Thread.Sleep(500);
            }

            // SAMP is closed
            // GeneralAPI.Instance.ResetInitialize();
        }
    }
}