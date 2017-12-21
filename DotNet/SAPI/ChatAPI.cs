using SAPI.Util;
using System;
using System.Runtime.InteropServices;
using System.Text;

namespace SAPI
{
    public class ChatAPI : Singleton<ChatAPI>
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_AddBufferMessage(string message);
        private API_AddBufferMessage API_addBufferMessage;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_AddMessage(string message);
        private API_AddMessage API_addMessage;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_Clear();
        private API_Clear API_clear;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_GetText(StringBuilder stringBuilder, int maxLength);
        private API_GetText API_getText;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_SetText(string text);
        private API_SetText API_setText;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_IsOpen();
        private API_IsOpen API_isOpen;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_Toggle(bool open);
        private API_Toggle API_toggle;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_Send(string message);
        private API_Send API_send;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetCursorPosition1(int begin, int end);
        private API_SetCursorPosition1 API_setCursorPosition1;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SetCursorPosition2(int position);
        private API_SetCursorPosition2 API_setCursorPosition2;

        public ChatAPI()
        {
            this.API_addBufferMessage = (API_AddBufferMessage)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?AddBufferMessage@Chat@SAMP@API@@YAXPB_W@Z"), typeof(API_AddBufferMessage));
            this.API_addMessage = (API_AddMessage)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?AddMessage@Chat@SAMP@API@@YAXPB_W@Z"), typeof(API_AddMessage));
            this.API_clear = (API_Clear)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Clear@Chat@SAMP@API@@YAXXZ"), typeof(API_Clear));
            this.API_getText = (API_GetText)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetText@Chat@SAMP@API@@YAXPA_WH@Z"), typeof(API_GetText));
            this.API_setText = (API_SetText)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetText@Chat@SAMP@API@@YAXPB_W@Z"), typeof(API_SetText));
            this.API_isOpen = (API_IsOpen)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?IsOpen@Chat@SAMP@API@@YA_NXZ"), typeof(API_IsOpen));
            this.API_toggle = (API_Toggle)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Toggle@Chat@SAMP@API@@YAX_N@Z"), typeof(API_Toggle));
            this.API_send = (API_Send)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Send@Chat@SAMP@API@@YAXPB_W@Z"), typeof(API_Send));
            this.API_setCursorPosition1 = (API_SetCursorPosition1)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetCursorPosition@Chat@SAMP@API@@YAXH@Z"), typeof(API_SetCursorPosition1));
            this.API_setCursorPosition2 = (API_SetCursorPosition2)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetCursorPosition@Chat@SAMP@API@@YAXHH@Z"), typeof(API_SetCursorPosition2));
        }

        public void AddBufferMessage(string message)
        {
            this.API_addBufferMessage.Invoke(message);
        }

        public void AddMessage(string message)
        {
            this.API_addMessage.Invoke(message);
        }

        public void Clear()
        {
            this.API_clear.Invoke();
        }

        public string GetText()
        {
            var stringBuilder = new StringBuilder(1024);
            this.API_getText(stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }

        public void SetText(string text)
        {
            this.API_setText(text);
        }

        public bool IsOpen()
        {
            return this.API_isOpen.Invoke();
        }

        public void Toggle(bool open)
        {
            this.API_toggle.Invoke(open);
        }

        public void Send(string message)
        {
            this.API_send.Invoke(message);
        }

        public void SetCursorPosition(int begin, int end)
        {
            this.API_setCursorPosition1.Invoke(begin, end);
        }
    }
}
