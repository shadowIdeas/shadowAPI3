using SAPI.Util;
using System;
using System.IO;
using System.Runtime.InteropServices;

namespace SAPI
{
    public class GeneralAPI : Singleton<GeneralAPI>
    {
        private const string FILE_NAME = "API";

        private IntPtr handle;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate int API_Initialize(string fullPath, string file);
        private API_Initialize API_initialize;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_ResetInitialize();
        private API_ResetInitialize API_resetInitialize;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_GetWeatherID();
        private API_GetWeatherID API_getWeatherID;

        public GeneralAPI()
        {
            if (File.Exists($"{FILE_NAME}.dll"))
            {
                this.handle = Interop.LoadLibrary(FILE_NAME);
                this.API_initialize = (API_Initialize)Marshal.GetDelegateForFunctionPointer(GetFunctionPointer("?Initialize@API@@YAHPB_W0@Z"), typeof(API_Initialize));
                this.API_resetInitialize = (API_ResetInitialize)Marshal.GetDelegateForFunctionPointer(GetFunctionPointer("?ResetInitialize@API@@YAXXZ"), typeof(API_ResetInitialize));
                this.API_getWeatherID = (API_GetWeatherID)Marshal.GetDelegateForFunctionPointer(GetFunctionPointer("?GetWeatherID@Other@API@@YAHXZ"), typeof(API_GetWeatherID));
            }
            else
            {
                throw new FileNotFoundException();
            }
        }

        public IntPtr GetFunctionPointer(string functionName)
        {
            IntPtr ptr = Interop.GetProcAddress(handle, functionName);
            return ptr;
        }

        /// <summary>
        /// Load the API
        /// </summary>
        public int Initialize()
        {
            var path = Environment.CurrentDirectory;
            return this.API_initialize.Invoke($"{path}\\{FILE_NAME}.dll", FILE_NAME);
        }

        /// <summary>
        /// Before reloading the API (e.g. when the game was closed), call this
        /// </summary>
        public void ResetInitialize()
        {
            this.API_resetInitialize.Invoke();
        }

        public int GetWeatherID()
        {
            return this.API_getWeatherID();
        }
    }
}