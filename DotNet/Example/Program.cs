using SAPI;
using SAPI.Overlay;
using System;
using System.Threading;
using System.Threading.Tasks;

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

            //ChatAPI.Instance.Send("Hello");

            //var textID = TextAPI.Instance.Create();
            //TextAPI.Instance.SetActive(textID, true);
            //TextAPI.Instance.SetText(textID, "Mobiler Daten Computer\nName: Kayne.Walter\nWantedanzahl: 13\nGrund: Flucht(-versuch) 18:21\n(Von Kayne.Walter)\nF[334s} M[100s] A[82s]");
            //TextAPI.Instance.SetUseMaxWidth(textID, true);
            //TextAPI.Instance.SetUseMaxHeight(textID, true);
            //TextAPI.Instance.SetX(textID, 500);
            //TextAPI.Instance.SetY(textID, 300);
            //TextAPI.Instance.SetMaxWidth(textID, 300);
            //TextAPI.Instance.SetMaxHeight(textID, 100);

            //d.Block(42, "Test");

            while (true)
            {
                Console.Clear();

                Parallel.For(0, 50, (i) =>
                {
                    Console.WriteLine($"i={i} Health: {p.GetHealth()}");
                });

                Console.WriteLine($"Health: {p.GetHealth()}");
                Thread.Sleep(500);
            }

            // SAMP is closed
            // GeneralAPI.Instance.ResetInitialize();
        }
    }
}