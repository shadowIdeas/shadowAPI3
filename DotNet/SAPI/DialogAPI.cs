using SAPI.Util;
using System.Runtime.InteropServices;
using System.Text;

namespace SAPI
{
    public class DialogAPI : Singleton<DialogAPI>
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_IsOpen();
        private API_IsOpen API_isOpen;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_Close(int reason);
        private API_Close API_close;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_GetID();
        private API_GetID API_getID;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_GetText(StringBuilder stringBuilder, int maxLength);
        private API_GetText API_getText;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_SetText(string text);
        private API_SetText API_setText;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void API_SelectIndex(int index);
        private API_SelectIndex API_selectIndex;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int API_GetStringCount();
        private API_GetStringCount API_getStringCount;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_GetStringByIndex(int index, StringBuilder stringBuilder, int maxLength);
        private API_GetStringByIndex API_getStringByIndex;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_Block(int dialogID, string text);
        private API_Block API_block;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_BlockHasBlockedDialog();
        private API_BlockHasBlockedDialog API_blockHasBlockedDialog;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private delegate bool API_BlockNeedBlocking();
        private API_BlockNeedBlocking API_blockNeedBlocking;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_BlockGetCaption(StringBuilder stringBuilder, int maxLength);
        private API_BlockGetCaption API_blockGetCaption;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private delegate void API_BlockGetText(StringBuilder stringBuilder, int maxLength);
        private API_BlockGetText API_blockGetText;

        public DialogAPI()
        {
            this.API_isOpen = (API_IsOpen)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?IsOpen@Dialog@SAMP@API@@YA_NXZ"), typeof(API_IsOpen));
            this.API_close = (API_Close)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Close@Dialog@SAMP@API@@YAXH@Z"), typeof(API_Close));
            this.API_getID = (API_GetID)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetID@Dialog@SAMP@API@@YAHXZ"), typeof(API_GetID));
            this.API_getText = (API_GetText)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetText@Dialog@SAMP@API@@YAXPA_WH@Z"), typeof(API_GetText));
            this.API_setText = (API_SetText)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SetText@Dialog@SAMP@API@@YAXPB_W@Z"), typeof(API_SetText));
            this.API_selectIndex = (API_SelectIndex)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?SelectIndex@Dialog@SAMP@API@@YAXH@Z"), typeof(API_SelectIndex));
            this.API_getStringCount = (API_GetStringCount)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetStringCount@Dialog@SAMP@API@@YAHXZ"), typeof(API_GetStringCount));
            this.API_getStringByIndex = (API_GetStringByIndex)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?GetStringByIndex@Dialog@SAMP@API@@YAXHPA_WH@Z"), typeof(API_GetStringByIndex));
            this.API_block = (API_Block)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?Block@Dialog@SAMP@API@@YAXHPB_W@Z"), typeof(API_Block));
            this.API_blockHasBlockedDialog = (API_BlockHasBlockedDialog)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?BlockHasBlockedDialog@Dialog@SAMP@API@@YA_NXZ"), typeof(API_BlockHasBlockedDialog));
            this.API_blockNeedBlocking = (API_BlockNeedBlocking)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?BlockHasNeedBlocking@Dialog@SAMP@API@@YA_NXZ"), typeof(API_BlockNeedBlocking));
            this.API_blockGetCaption = (API_BlockGetCaption)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?BlockGetCaption@Dialog@SAMP@API@@YAXPA_WH@Z"), typeof(API_BlockGetCaption));
            this.API_blockGetText = (API_BlockGetText)Marshal.GetDelegateForFunctionPointer(GeneralAPI.Instance.GetFunctionPointer("?BlockGetText@Dialog@SAMP@API@@YAXPA_WH@Z"), typeof(API_BlockGetText));
        }

        public bool IsOpen()
        {
            return this.API_isOpen();
        }

        public void Close(int reason)
        {
            this.API_close.Invoke(reason);
        }

        public int GetID()
        {
            return this.API_getID.Invoke();
        }

        public string GetText()
        {
            var stringBuilder = new StringBuilder(1024);

            this.API_getText.Invoke(stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }

        public void SetText(string text)
        {
            this.API_setText.Invoke(text);
        }

        public void SelectIndex(int index)
        {
            this.API_selectIndex.Invoke(index);
        }

        public int GetStringCount()
        {
            return this.API_getStringCount.Invoke();
        }

        public string GetStringByIndex(int index)
        {
            var stringBuilder = new StringBuilder(1024);

            this.API_getStringByIndex.Invoke(index, stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }

        public void Block(int dialogID, string text)
        {
            this.API_block.Invoke(dialogID, text);
        }

        public bool BlockHasBlockedDialog()
        {
            return this.API_blockHasBlockedDialog.Invoke();
        }

        public bool BlockNeedBlocking()
        {
            return this.API_blockNeedBlocking.Invoke();
        }

        public string BlockGetCaption()
        {
            var stringBuilder = new StringBuilder(1024);

            this.API_blockGetCaption.Invoke(stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }

        public string BlockGetText()
        {
            var stringBuilder = new StringBuilder(8092);

            this.API_blockGetText.Invoke(stringBuilder, stringBuilder.Capacity);

            return stringBuilder.ToString();
        }
    }
}
