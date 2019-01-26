using SAPI.Util;
using System.Runtime.InteropServices;
using System.Text;

namespace SAPI
{
    public class PlayerAPI : Singleton<PlayerAPI>
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_GetHealth();
        private API_GetHealth API_getHealth;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_GetArmor();
        private API_GetArmor API_getArmor;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_InInterior();
        private API_InInterior API_inInterior;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_InVehicle();
        private API_InVehicle API_inVehicle;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_IsDriver();
        private API_IsDriver API_isDriver;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_IsFreezed();
        private API_IsFreezed API_isFreezed;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate float API_GetYaw();
        private API_GetYaw API_getYaw;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_GetInteriorId();
        private API_GetInteriorId API_getInteriorId;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_GetPosition(ref float x, ref float y, ref float z);
        private API_GetPosition API_getPosition;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_GetCity(StringBuilder stringBuilder, int maxLength);
        private API_GetCity API_getCity;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_GetDistrict(StringBuilder stringBuilder, int maxLength);
        private API_GetDistrict API_getDistrict;

        public PlayerAPI()
        {
            this.API_getHealth = (API_GetHealth)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetHealth@Player@API@@YAHXZ"), typeof(API_GetHealth));
            this.API_getArmor = (API_GetArmor)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetArmor@Player@API@@YAHXZ"), typeof(API_GetArmor));
            this.API_inInterior = (API_InInterior)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?InInterior@Player@API@@YA_NXZ"), typeof(API_InInterior));
            this.API_inVehicle = (API_InVehicle)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?InVehicle@Player@API@@YA_NXZ"), typeof(API_InVehicle));
            this.API_isDriver = (API_IsDriver)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?IsDriver@Player@API@@YA_NXZ"), typeof(API_IsDriver));
            this.API_isFreezed = (API_IsFreezed)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?IsFreezed@Player@API@@YA_NXZ"), typeof(API_IsFreezed));
            this.API_getYaw = (API_GetYaw)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetYaw@Player@API@@YAMXZ"), typeof(API_GetYaw));
            this.API_getInteriorId = (API_GetInteriorId)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetInteriorId@Player@API@@YAHXZ"), typeof(API_GetInteriorId));
            this.API_getPosition = (API_GetPosition)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetPosition@Player@API@@YAXAAM00@Z"), typeof(API_GetPosition));
            this.API_getCity = (API_GetCity)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetCity@Player@API@@YAXPA_WH@Z"), typeof(API_GetCity));
            this.API_getDistrict = (API_GetDistrict)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetDistrict@Player@API@@YAXPA_WH@Z"), typeof(API_GetDistrict));
        }

        public int GetHealth()
        {
            return this.API_getHealth.Invoke();
        }

        public int GetArmor()
        {
            return this.API_getArmor.Invoke();
        }

        public bool InInterior()
        {
            return this.API_inInterior.Invoke();
        }

        public bool InVehicle()
        {
            return this.API_inVehicle.Invoke();
        }

        public bool IsDriver()
        {
            return this.API_isDriver.Invoke();
        }

        public bool IsFreezed()
        {
            return this.API_isFreezed.Invoke();
        }

        public float GetYaw()
        {
            return this.API_getYaw.Invoke();
        }

        public int GetInteriorId()
        {
            return API_getInteriorId.Invoke();
        }

        public void GetPosition(out float x, out float y, out float z)
        {
            float lX, lY, lZ;
            lX = lY = lZ = 0.0f;

            this.API_getPosition.Invoke(ref lX, ref lY, ref lZ);

            x = lX;
            y = lY;
            z = lZ;
        }

        public string GetCity()
        {
            var stringBuilder = new StringBuilder(1024);

            this.API_getCity.Invoke(stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }

        public string GetDistrict()
        {
            var stringBuilder = new StringBuilder(1024);

            this.API_getDistrict.Invoke(stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }

        public bool InRadius(float x, float y, float z, float radius)
        {
            GetPosition(out float currentX, out float currentY, out float currentZ);

            x = currentX - x;
            y = currentY - y;
            z = currentZ - z;

            if ((x < radius) && (x > -radius) && (y < radius) && (y > -radius) && (z < radius) && (z > -radius))
                return true;

            return false;
        }
    }
}
