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

            Random random = new Random();
            System.Collections.Generic.List<int> overlays = new System.Collections.Generic.List<int>();
            
            while (true)
            {
                Console.Clear();

                Parallel.For(0, 50, (i) =>
                {
                    Console.WriteLine($"i={i} Health: {p.GetHealth()}");
                });

                foreach (var item in overlays)
                    t.Delete(item);
                overlays.Clear();

                for (int i = 0; i < 50; i++)
                {
                    int y = b.Create();
                    b.SetActive(y, true);
                    b.SetColor(y, (uint)random.Next(int.MaxValue));
                    b.SetWidth(y, random.Next(0, 700));
                    b.SetHeight(y, random.Next(0, 700));
                    b.SetX(y, random.Next(0, 700));
                    b.SetY(y, random.Next(0, 700));

                    overlays.Add(y);
                }

                for (int i = 0; i < 50; i++)
                {
                    int y = t.Create();
                    t.SetActive(y, true);
                    t.SetColor(y, (uint)random.Next(int.MaxValue));
                    t.SetX(y, random.Next(0, 700));
                    t.SetY(y, random.Next(0, 700));
                    t.SetSize(y, random.Next(0, 28));

                    System.Text.StringBuilder bu = new System.Text.StringBuilder();
                    for (int j = 0; j < random.Next(64); j++)
                        bu.Append((char)(random.Next(0, 0xFFFF)));

                    t.SetText(y, bu.ToString());

                    overlays.Add(y);
                }

                Thread.Sleep(5000);
            }

            // SAMP is closed
            // GeneralAPI.Instance.ResetInitialize();
        }
    }
}