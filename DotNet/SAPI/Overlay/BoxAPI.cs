using SAPI.Util;
using System.Runtime.InteropServices;

namespace SAPI.Overlay
{
    public class BoxAPI : Singleton<BoxAPI>
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_Create();
        private API_Create API_create;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_Delete(int id);
        private API_Delete API_delete;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetColor(int id, uint color);
        private API_SetColor API_setColor;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetX(int id, int x);
        private API_SetX API_setX;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetY(int id, int y);
        private API_SetY API_setY;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetWidth(int id, int width);
        private API_SetWidth API_setWidth;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetHeight(int id, int height);
        private API_SetHeight API_setHeight;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetActive(int id, bool active);
        private API_SetActive API_setActive;

        public BoxAPI()
        {
            this.API_create = (API_Create)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Create@Box@Overlay@API@@YAHXZ"), typeof(API_Create));
            this.API_delete = (API_Delete)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Delete@Box@Overlay@API@@YAXH@Z"), typeof(API_Delete));
            this.API_setColor = (API_SetColor)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetColor@Box@Overlay@API@@YAXHK@Z"), typeof(API_SetColor));
            this.API_setX = (API_SetX)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetX@Box@Overlay@API@@YAXHH@Z"), typeof(API_SetX));
            this.API_setY = (API_SetY)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetY@Box@Overlay@API@@YAXHH@Z"), typeof(API_SetY));
            this.API_setWidth = (API_SetWidth)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetWidth@Box@Overlay@API@@YAXHH@Z"), typeof(API_SetWidth));
            this.API_setHeight = (API_SetHeight)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetHeight@Box@Overlay@API@@YAXHH@Z"), typeof(API_SetHeight));
            this.API_setActive = (API_SetActive)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetActive@Box@Overlay@API@@YAXH_N@Z"), typeof(API_SetActive));
        }

        public int Create()
        {
            return this.API_create.Invoke();
        }

        public void Delete(int id)
        {
            this.API_delete.Invoke(id);
        }

        public void SetColor(int id, uint color)
        {
            this.API_setColor.Invoke(id, color);
        }

        public void SetX(int id, int x)
        {
            this.API_setX.Invoke(id, x);
        }

        public void SetY(int id, int y)
        {
            this.API_setY.Invoke(id, y);
        }

        public void SetWidth(int id, int width)
        {
            this.API_setWidth.Invoke(id, width);
        }

        public void SetHeight(int id, int height)
        {
            this.API_setHeight.Invoke(id, height);
        }

        public void SetActive(int id, bool active)
        {
            this.API_setActive.Invoke(id, active);
        }
    }
}
