using SAPI.Util;
using System.Runtime.InteropServices;

namespace SAPI.Overlay
{
    public class TextAPI : Singleton<TextAPI>
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_Create();
        private API_Create API_create;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_Delete(int id);
        private API_Delete API_delete;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_SetText(int id, string text);
        private API_SetText API_setText;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetSize(int id, int size);
        private API_SetSize API_setSize;

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
        private delegate void API_SetActive(int id, bool active);
        private API_SetActive API_setActive;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetUseMaxWidth(int id, bool useMaxWidth);
        private API_SetUseMaxWidth API_setUseMaxWidth;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetUseMaxHeight(int id, bool useMaxHeight);
        private API_SetUseMaxHeight API_setUseMaxHeight;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetMaxWidth(int id, int maxWidth);
        private API_SetMaxWidth API_setMaxWidth;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetMaxHeight(int id, int maxHeight);
        private API_SetMaxHeight API_setMaxHeight;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_GetTextExtent(int id, out int width, out int height);
        private API_GetTextExtent API_getTextExtent;

        public TextAPI()
        {
            this.API_create = (API_Create)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Create@Text@Overlay@API@@YAHXZ"), typeof(API_Create));
            this.API_delete = (API_Delete)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Delete@Text@Overlay@API@@YAXH@Z"), typeof(API_Delete));
            this.API_setText = (API_SetText)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetText@Text@Overlay@API@@YAXHPB_W@Z"), typeof(API_SetText));
            this.API_setSize = (API_SetSize)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetSize@Text@Overlay@API@@YAXHH@Z"), typeof(API_SetSize));
            this.API_setColor = (API_SetColor)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetColor@Text@Overlay@API@@YAXHK@Z"), typeof(API_SetColor));
            this.API_setX = (API_SetX)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetX@Text@Overlay@API@@YAXHH@Z"), typeof(API_SetX));
            this.API_setY = (API_SetY)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetY@Text@Overlay@API@@YAXHH@Z"), typeof(API_SetY));
            this.API_setActive = (API_SetActive)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetActive@Text@Overlay@API@@YAXH_N@Z"), typeof(API_SetActive));
            this.API_setUseMaxWidth = (API_SetUseMaxWidth)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetUseMaxWidth@Text@Overlay@API@@YAXH_N@Z"), typeof(API_SetUseMaxWidth));
            this.API_setUseMaxHeight = (API_SetUseMaxHeight)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetUseMaxHeight@Text@Overlay@API@@YAXH_N@Z"), typeof(API_SetUseMaxHeight));
            this.API_setMaxWidth = (API_SetMaxWidth)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetMaxWidth@Text@Overlay@API@@YAXHH@Z"), typeof(API_SetMaxWidth));
            this.API_setMaxHeight = (API_SetMaxHeight)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetMaxHeight@Text@Overlay@API@@YAXHH@Z"), typeof(API_SetMaxHeight));
            this.API_getTextExtent = (API_GetTextExtent)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetTextExtent@Text@Overlay@API@@YAXHAAH0@Z"), typeof(API_GetTextExtent));
        }

        public int Create()
        {
            return this.API_create.Invoke();
        }

        public void Delete(int id)
        {
            this.API_delete.Invoke(id);
        }

        public void SetText(int id, string text)
        {
            this.API_setText.Invoke(id, text);
        }

        public void SetSize(int id, int size)
        {
            this.API_setSize.Invoke(id, size);
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

        public void SetActive(int id, bool active)
        {
            this.API_setActive.Invoke(id, active);
        }

        public void SetUseMaxWidth(int id, bool useMaxWidth)
        {
            this.API_setUseMaxWidth.Invoke(id, useMaxWidth);
        }

        public void SetUseMaxHeight(int id, bool useMaxHeight)
        {
            this.API_setUseMaxHeight.Invoke(id, useMaxHeight);
        }

        public void SetMaxWidth(int id, int maxWidth)
        {
            this.API_setMaxWidth.Invoke(id, maxWidth);
        }

        public void SetMaxHeight(int id, int maxHeight)
        {
            this.API_setMaxHeight.Invoke(id, maxHeight);
        }

        public void GetTextExtent(int id, out int width, out int height)
        {
            this.API_getTextExtent.Invoke(id, out width, out height);
        }
    }
}
