using SAPI.Util;
using System.Runtime.InteropServices;

namespace SAPI.SAMP
{
    public class VehicleAPI : Singleton<VehicleAPI>
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_ToggleSiren(bool state);
        private API_ToggleSiren API_toggleSiren;

        public VehicleAPI()
        {
            this.API_toggleSiren = (API_ToggleSiren)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?ToggleSiren@Vehicle@SAMP@API@@YAX_N@Z"), typeof(API_ToggleSiren));
        }

        public void ToggleSiren(bool state)
        {
            this.API_toggleSiren.Invoke(state);
        }
    }
}
