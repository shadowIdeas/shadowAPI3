using SAPI.Util;
using System.Runtime.InteropServices;
using System.Text;

namespace SAPI.SAMP
{
    public class PlayerAPI : Singleton<PlayerAPI>
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_GetFullName(string name, StringBuilder stringBuilder, int maxLength);
        private API_GetFullName API_getFullName;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate int API_GetIDByName(string name);
        private API_GetIDByName API_getIDByName;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_GetNameByID(int id, StringBuilder stringBuilder, int maxLength);
        private API_GetNameByID API_getNameByID;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_GetLocalID();
        private API_GetLocalID API_getLocalID;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_GetLocalName(StringBuilder stringBuilder, int maxLength);
        private API_GetLocalName API_getLocalName;

        public PlayerAPI()
        {
            this.API_getFullName = (API_GetFullName)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetFullName@Player@SAMP@API@@YAXPB_WPA_WH@Z"), typeof(API_GetFullName));
            this.API_getIDByName = (API_GetIDByName)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetIdByName@Player@SAMP@API@@YAHPB_W@Z"), typeof(API_GetIDByName));
            this.API_getNameByID = (API_GetNameByID)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetNameById@Player@SAMP@API@@YAXHPA_WH@Z"), typeof(API_GetNameByID));
            this.API_getLocalID = (API_GetLocalID)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetLocalId@Player@SAMP@API@@YAHXZ"), typeof(API_GetLocalID));
            this.API_getLocalName = (API_GetLocalName)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetLocalName@Player@SAMP@API@@YAXPA_WH@Z"), typeof(API_GetLocalName));
        }

        public string GetFullName(string name)
        {
            var stringBuilder = new StringBuilder(1024);

            this.API_getFullName.Invoke(name, stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }

        public int GetIDByName(string name)
        {
            return this.API_getIDByName.Invoke(name);
        }

        public string GetNameByID(int id)
        {
            var stringBuilder = new StringBuilder(1024);

            this.API_getNameByID.Invoke(id, stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }

        public int GetLocalID()
        {
            return this.API_getLocalID.Invoke();
        }

        public string GetLocalName()
        {
            var stringBuilder = new StringBuilder(1024);

            this.API_getLocalName.Invoke(stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }
    }
}
