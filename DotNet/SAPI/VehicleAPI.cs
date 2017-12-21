using SAPI.Util;
using System.Runtime.InteropServices;

namespace SAPI
{
    public class VehicleAPI : Singleton<VehicleAPI>
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate float API_GetHealth();
        private API_GetHealth API_getHealth;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_GetModelID();
        private API_GetModelID API_getModelID;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate float API_GetSpeed();
        private API_GetSpeed API_getSpeed;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_IsEngineRunning();
        private API_IsEngineRunning API_isEngineRunning;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_IsLightActive();
        private API_IsLightActive API_isLightActive;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_IsLocked();
        private API_IsLocked API_isLocked;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_UseHorn();
        private API_UseHorn API_useHorn;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_UseSiren();
        private API_UseSiren API_useSiren;

        public VehicleAPI()
        {
            this.API_getHealth = (API_GetHealth)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetHealth@Vehicle@API@@YAMXZ"), typeof(API_GetHealth));
            this.API_getModelID = (API_GetModelID)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetModelID@Vehicle@API@@YAHXZ"), typeof(API_GetModelID));
            this.API_getSpeed = (API_GetSpeed)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetSpeed@Vehicle@API@@YAMXZ"), typeof(API_GetSpeed));
            this.API_isEngineRunning = (API_IsEngineRunning)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?IsEngineRunning@Vehicle@API@@YA_NXZ"), typeof(API_IsEngineRunning));
            this.API_isLightActive = (API_IsLightActive)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?IsLightActive@Vehicle@API@@YA_NXZ"), typeof(API_IsLightActive));
            this.API_isLocked = (API_IsLocked)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?IsLocked@Vehicle@API@@YA_NXZ"), typeof(API_IsLocked));
            this.API_useHorn = (API_UseHorn)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?UseHorn@Vehicle@API@@YA_NXZ"), typeof(API_UseHorn));
            this.API_useSiren = (API_UseSiren)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?UseSiren@Vehicle@API@@YA_NXZ"), typeof(API_UseSiren));
        }

        public float GetHealth()
        {
            return this.API_getHealth.Invoke();
        }

        public int GetModelID()
        {
            return this.API_getModelID.Invoke();
        }

        public float GetSpeed()
        {
            return this.API_getSpeed.Invoke();
        }

        public bool IsEngineRunning()
        {
            return this.API_isEngineRunning.Invoke();
        }

        public bool IsLightActive()
        {
            return this.API_isLightActive.Invoke();
        }

        public bool IsLocked()
        {
            return this.API_isLocked.Invoke();
        }

        public bool UseHorn()
        {
            return this.API_useHorn.Invoke();
        }

        public bool UseSiren()
        {
            return this.API_useSiren.Invoke();
        }
    }
}
