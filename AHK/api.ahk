class API {
    static _initialized := false
    static _handle := 0

    _initialize() {
        if (!API._initialized) {
            API._initialized := true
            API._handle := DllCall("LoadLibraryW", "WStr", "API.dll", "Ptr", "Cdecl")
            
            API.General._initialize := API._loadAddress("?Initialize@API@@YAHPB_W0@Z")
            API.General._resetInitialize := API._loadAddress("?ResetInitialize@API@@YAXXZ")
            API.General._getWeatherId := API._loadAddress("?GetWeatherID@Other@API@@YAHXZ")
            API.General._setKey := API._loadAddress("?SetKey@Other@API@@YAHH_N@Z")

            API.Chat._addBufferMessage := API._loadAddress("?AddBufferMessage@Chat@SAMP@API@@YAXPB_W@Z")
            API.Chat._addMessage := API._loadAddress("?AddMessage@Chat@SAMP@API@@YAXPB_W@Z")
            API.Chat._clear := API._loadAddress("?Clear@Chat@SAMP@API@@YAXXZ")
            API.Chat._getText := API._loadAddress("?GetText@Chat@SAMP@API@@YAXPA_WH@Z")
            API.Chat._setText := API._loadAddress("?SetText@Chat@SAMP@API@@YAXPB_W@Z")
            API.Chat._isOpen := API._loadAddress("?IsOpen@Chat@SAMP@API@@YA_NXZ")
            API.Chat._toggle := API._loadAddress("?Toggle@Chat@SAMP@API@@YAX_N@Z")
            API.Chat._send := API._loadAddress("?Send@Chat@SAMP@API@@YAXPB_W@Z")
            API.Chat._setCursorPosition := API._loadAddress("?SetCursorPosition@Chat@SAMP@API@@YAXHH@Z")

            API.Dialog._getText := API._loadAddress("?GetText@Dialog@SAMP@API@@YAXPA_WH@Z")
            API.Dialog._setText := API._loadAddress("?SetText@Dialog@SAMP@API@@YAXPB_W@Z")
            API.Dialog._getID := API._loadAddress("?GetID@Dialog@SAMP@API@@YAHXZ")
            API.Dialog._getStringCount := API._loadAddress("?GetStringCount@Dialog@SAMP@API@@YAHXZ")
            API.Dialog._getStringByIndex := API._loadAddress("?GetStringByIndex@Dialog@SAMP@API@@YAXHPA_WH@Z")
            API.Dialog._isOpen := API._loadAddress("?IsOpen@Dialog@SAMP@API@@YA_NXZ")
            API.Dialog._close := API._loadAddress("?Close@Dialog@SAMP@API@@YAXH@Z")
            API.Dialog._selectIndex := API._loadAddress("?SelectIndex@Dialog@SAMP@API@@YAXH@Z")
            API.Dialog._blockGetCaption := API._loadAddress("?BlockGetCaption@Dialog@SAMP@API@@YAXPA_WH@Z")
            API.Dialog._blockGetText := API._loadAddress("?BlockGetText@Dialog@SAMP@API@@YAXPA_WH@Z")
            API.Dialog._block := API._loadAddress("?Block@Dialog@SAMP@API@@YAXHPB_W@Z")
            API.Dialog._blockHasBlockedDialog := API._loadAddress("?BlockHasBlockedDialog@Dialog@SAMP@API@@YA_NXZ")
            API.Dialog._blockHasNeedBlocking := API._loadAddress("?BlockHasNeedBlocking@Dialog@SAMP@API@@YA_NXZ")

            API.Box._create := API._loadAddress("?Create@Box@Overlay@API@@YAHXZ")
            API.Box._delete := API._loadAddress("?Delete@Box@Overlay@API@@YAXH@Z")
            API.Box._setColor := API._loadAddress("?SetColor@Box@Overlay@API@@YAXHK@Z")
            API.Box._setX := API._loadAddress("?SetX@Box@Overlay@API@@YAXHH@Z")
            API.Box._setY := API._loadAddress("?SetY@Box@Overlay@API@@YAXHH@Z")
            API.Box._setWidth := API._loadAddress("?SetWidth@Box@Overlay@API@@YAXHH@Z")
            API.Box._setHeight := API._loadAddress("?SetHeight@Box@Overlay@API@@YAXHH@Z")
            API.Box._setActive := API._loadAddress("?SetActive@Box@Overlay@API@@YAXH_N@Z")

            API.Text._create := API._loadAddress("?Create@Text@Overlay@API@@YAHXZ")
            API.Text._delete := API._loadAddress("?Delete@Text@Overlay@API@@YAXH@Z")
            API.Text._setColor := API._loadAddress("?SetColor@Text@Overlay@API@@YAXHK@Z")
            API.Text._setX := API._loadAddress("?SetX@Text@Overlay@API@@YAXHH@Z")
            API.Text._setY := API._loadAddress("?SetY@Text@Overlay@API@@YAXHH@Z")
            API.Text._setMaxWidth := API._loadAddress("?SetMaxWidth@Text@Overlay@API@@YAXHH@Z")
            API.Text._setMaxHeight := API._loadAddress("?SetMaxHeight@Text@Overlay@API@@YAXHH@Z")
            API.Text._setActive := API._loadAddress("?SetActive@Text@Overlay@API@@YAXH_N@Z")
            API.Text._setText := API._loadAddress("?SetText@Text@Overlay@API@@YAXHPB_W@Z")
            API.Text._setSize := API._loadAddress("?SetSize@Text@Overlay@API@@YAXHH@Z")
            API.Text._setUseMaxWidth := API._loadAddress("?SetUseMaxWidth@Text@Overlay@API@@YAXH_N@Z")
            API.Text._setUseMaxHeight := API._loadAddress("?SetUseMaxHeight@Text@Overlay@API@@YAXH_N@Z")
            API.Text._getTextExtent := API._loadAddress("?GetTextExtent@Text@Overlay@API@@YAXHAAH0@Z")

            API.Player._getHealth := API._loadAddress("?GetHealth@Player@API@@YAHXZ")
            API.Player._getArmor := API._loadAddress("?GetArmor@Player@API@@YAHXZ")
            API.Player._getInteriorId := API._loadAddress("?GetInteriorId@Player@API@@YAHXZ")
            API.Player._getCity := API._loadAddress("?GetCity@Player@API@@YAXPA_WH@Z")
            API.Player._getDistrict := API._loadAddress("?GetDistrict@Player@API@@YAXPA_WH@Z")
            API.Player._getPosition := API._loadAddress("?GetPosition@Player@API@@YAXAAM00@Z")
            API.Player._getYaw := API._loadAddress("?GetYaw@Player@API@@YAMXZ")
            API.Player._inInterior := API._loadAddress("?InInterior@Player@API@@YA_NXZ")
            API.Player._inVehicle := API._loadAddress("?InVehicle@Player@API@@YA_NXZ")
            API.Player._isDriver := API._loadAddress("?IsDriver@Player@API@@YA_NXZ")
            API.Player._isFreezed := API._loadAddress("?IsFreezed@Player@API@@YA_NXZ")
            API.Player._getLocalName := API._loadAddress("?GetLocalName@Player@SAMP@API@@YAXPA_WH@Z")
            API.Player._getLocalId := API._loadAddress("?GetLocalId@Player@SAMP@API@@YAHXZ")
            API.Player._getNameById := API._loadAddress("?GetNameById@Player@SAMP@API@@YAXHPA_WH@Z")
            API.Player._getIdByName := API._loadAddress("?GetIdByName@Player@SAMP@API@@YAHPB_W@Z")
            API.Player._getFullName := API._loadAddress("?GetFullName@Player@SAMP@API@@YAXPB_WPA_WH@Z")

            API.Vehicle._getSpeed := API._loadAddress("?GetSpeed@Vehicle@API@@YAMXZ")
            API.Vehicle._getHealth := API._loadAddress("?GetHealth@Vehicle@API@@YAMXZ")
            API.Vehicle._getModelID := API._loadAddress("?GetModelID@Vehicle@API@@YAHXZ")
            API.Vehicle._isLightActive := API._loadAddress("?IsLightActive@Vehicle@API@@YA_NXZ")
            API.Vehicle._isLocked := API._loadAddress("?IsLocked@Vehicle@API@@YA_NXZ")
            API.Vehicle._isEngineRunning := API._loadAddress("?IsEngineRunning@Vehicle@API@@YA_NXZ")
            API.Vehicle._useHorn := API._loadAddress("?UseHorn@Vehicle@API@@YA_NXZ")
            API.Vehicle._useSiren := API._loadAddress("?UseSiren@Vehicle@API@@YA_NXZ")
            API.Vehicle._getNumberplate := API._loadAddress("?GetNumberplate@Vehicle@SAMP@API@@YAXPA_WH@Z")
            API.Vehicle._toggleSiren := API._loadAddress("?ToggleSiren@Vehicle@SAMP@API@@YAX_N@Z")
        }
    }

    _loadAddress(name) {
        address := DllCall("GetProcAddress", "Ptr", API._handle, "AStr", name)
        if (address == 0) {
            MsgBox, Cant load %name%
        }

        return address
    }

    class General {
        static _initialize := 0
        static _resetInitialize := 0
        static _getWeatherId := 0
        static _setKey := 0

        initialize() {
            API._initialize()
            dir := A_ScriptDir
            path := dir "\API.dll"
            return DllCall(API.General._initialize, "WStr", path, "WStr", "API", "Cdecl Int")
        }

        resetInitialize() {
            API._initialize()
            DllCall(API.General._resetInitialize, "Cdecl")
        }

        getWeatherId() {
            API._initialize()
            return DllCall(API.General._getWeatherId, "Cdecl Int")
        }
		
        setKey(key, pressed) {
            API._initialize()
            DllCall(API.General._setKey, "Int", key, "Int", pressed, "Cdecl")
        }
    }

    class Chat {
		static _send := 0
		static _addMessage := 0
		static _getText := 0
		static _setText := 0
		static _getBufferMessage := 0
		static _addBufferMessage := 0
		static _setCursorPosition := 0
		static _toggle := 0
		static _clear := 0
		static _isOpen := 0
		send(message) {
			API._initialize()
			DllCall(API.Chat._send, "WStr", message, "Cdecl")
		}
		addMessage(message) {
			API._initialize()
			DllCall(API.Chat._addMessage, "WStr", message, "Cdecl")
		}
		getText(ByRef text, length) {
			API._initialize()
            VarSetCapacity(text, 2*length, 0)
			DllCall(API.Chat._getText, "WStr", text, "Int", length, "Cdecl")
		}
		setText(text) {
			API._initialize()
			DllCall(API.Chat._setText, "WStr", text, "Cdecl")
		}
		getBufferMessage(index, ByRef message, length) {
			API._initialize()
            VarSetCapacity(message, 2*length, 0)
			DllCall(API.Chat._getBufferMessage, "Int", index, "WStr", message, "Int", length, "Cdecl")
		}
		addBufferMessage(message) {
			API._initialize()
			DllCall(API.Chat._addBufferMessage, "WStr", message, "Cdecl")
		}
		setCursorPosition(indexStart, indexEnd) {
			API._initialize()
			DllCall(API.Chat._setCursorPosition, "Int", indexStart, "Int", indexEnd, "Cdecl")
		}
		toggle(state) {
			API._initialize()
			DllCall(API.Chat._toggle, "Int", state, "Cdecl")
		}
		clear() {
			API._initialize()
			DllCall(API.Chat._clear, "Cdecl")
		}
		isOpen() {
			API._initialize()
			return DllCall(API.Chat._isOpen, "Cdecl Int")
		}
	}
	class Dialog {
		static _getText := 0
		static _setText := 0
		static _clearText := 0
		static _setCursorPosition := 0
		static _getID := 0
		static _getStringCount := 0
		static _getStringByIndex := 0
		static _isOpen := 0
		static _close := 0
		static _selectIndex := 0
		static _blockGetCaption := 0
		static _blockGetText := 0
		static _block := 0
		static _blockHasBlockedDialog := 0
		static _blockHasNeedBlocking := 0
		getText(ByRef text, length) {
			API._initialize()
            VarSetCapacity(text, 2*length, 0)
			DllCall(API.Dialog._getText, "WStr", text, "Int", length, "Cdecl")
		}
		setText(text) {
			API._initialize()
			DllCall(API.Dialog._setText, "WStr", text, "Cdecl")
		}
		clearText() {
			API._initialize()
			DllCall(API.Dialog._clearText, "Cdecl")
		}
		setCursorPosition(indexStart, indexEnd) {
			API._initialize()
			DllCall(API.Dialog._setCursorPosition, "Int", indexStart, "Int", indexEnd, "Cdecl")
		}
		getID() {
			API._initialize()
			return DllCall(API.Dialog._getID, "Cdecl Int")
		}
		getStringCount() {
			API._initialize()
			return DllCall(API.Dialog._getStringCount, "Cdecl Int")
		}
		getStringByIndex(index, ByRef text, length) {
			API._initialize()
            VarSetCapacity(text, 2*length, 0)
			DllCall(API.Dialog._getStringByIndex, "Int", index, "WStr", text, "Int", length, "Cdecl")
		}
		isOpen() {
			API._initialize()
			return DllCall(API.Dialog._isOpen, "Cdecl Int")
		}
		close(reason) {
			API._initialize()
			DllCall(API.Dialog._close, "Int", reason, "Cdecl")
		}
		selectIndex(index) {
			API._initialize()
			DllCall(API.Dialog._selectIndex, "Int", index, "Cdecl")
		}
		blockGetCaption(ByRef caption, length) {
			API._initialize()
            VarSetCapacity(caption, 2*length, 0)
			DllCall(API.Dialog._blockGetCaption, "WStr", caption, "Int", length, "Cdecl")
		}
		blockGetText(ByRef text, length) {
			API._initialize()
            VarSetCapacity(text, 2*length, 0)
			DllCall(API.Dialog._blockGetText, "WStr", text, "Int", length, "Cdecl")
		}
		block(id, text) {
			API._initialize()
			DllCall(API.Dialog._block, "Int", id, "WStr", text, "Cdecl")
		}
		blockHasBlockedDialog() {
			API._initialize()
			return DllCall(API.Dialog._blockHasBlockedDialog, "Cdecl Int")
		}
		blockHasNeedBlocking() {
			API._initialize()
			return DllCall(API.Dialog._blockHasNeedBlocking, "Cdecl Int")
		}
	}
	class Box {
		static _create := 0
		static _delete := 0
		static _setColor := 0
		static _setX := 0
		static _setY := 0
		static _setWidth := 0
		static _setHeight := 0
		static _setActive := 0
		create() {
			API._initialize()
			return DllCall(API.Box._create, "Cdecl Int")
		}
		delete(id) {
			API._initialize()
			DllCall(API.Box._delete, "Int", id, "Cdecl")
		}
		setColor(id) {
			API._initialize()
			DllCall(API.Box._setColor, "Int", id, "Cdecl")
		}
		setX(id, x) {
			API._initialize()
			DllCall(API.Box._setX, "Int", id, "Int", x, "Cdecl")
		}
		setY(id, y) {
			API._initialize()
			DllCall(API.Box._setY, "Int", id, "Int", y, "Cdecl")
		}
		setWidth(id, width) {
			API._initialize()
			DllCall(API.Box._setWidth, "Int", id, "Int", width, "Cdecl")
		}
		setHeight(id, height) {
			API._initialize()
			DllCall(API.Box._setHeight, "Int", id, "Int", height, "Cdecl")
		}
		setActive(id, active) {
			API._initialize()
			DllCall(API.Box._setActive, "Int", id, "Int", active, "Cdecl")
		}
	}
	class Text {
		static _create := 0
		static _delete := 0
		static _setColor := 0
		static _setX := 0
		static _setY := 0
		static _setMaxWidth := 0
		static _setMaxHeight := 0
		static _setActive := 0
		static _setText := 0
		static _setSize := 0
		static _setUseMaxWidth := 0
		static _setUseMaxHeight := 0
		static _getTextExtent := 0
		create() {
			API._initialize()
			return DllCall(API.Text._create, "Cdecl Int")
		}
		delete(id) {
			API._initialize()
			DllCall(API.Text._delete, "Int", id, "Cdecl")
		}
		setColor(id) {
			API._initialize()
			DllCall(API.Text._setColor, "Int", id, "Cdecl")
		}
		setX(id, x) {
			API._initialize()
			DllCall(API.Text._setX, "Int", id, "Int", x, "Cdecl")
		}
		setY(id, y) {
			API._initialize()
			DllCall(API.Text._setY, "Int", id, "Int", y, "Cdecl")
		}
		setMaxWidth(id, maxWidth) {
			API._initialize()
			DllCall(API.Text._setMaxWidth, "Int", id, "Int", maxWidth, "Cdecl")
		}
		setMaxHeight(id, maxHeight) {
			API._initialize()
			DllCall(API.Text._setMaxHeight, "Int", id, "Int", maxHeight, "Cdecl")
		}
		setActive(id, active) {
			API._initialize()
			DllCall(API.Text._setActive, "Int", id, "Int", active, "Cdecl")
		}
		setText(id, text) {
			API._initialize()
			DllCall(API.Text._setText, "Int", id, "WStr", text, "Cdecl")
		}
		setSize(id, size) {
			API._initialize()
			DllCall(API.Text._setSize, "Int", id, "Int", size, "Cdecl")
		}
		setUseMaxWidth(id, state) {
			API._initialize()
			DllCall(API.Text._setUseMaxWidth, "Int", id, "Int", state, "Cdecl")
		}
		setUseMaxHeight(id, state) {
			API._initialize()
			DllCall(API.Text._setUseMaxHeight, "Int", id, "Int", state, "Cdecl")
		}
		getTextExtent(id, width, height) {
			API._initialize()
			DllCall(API.Text._getTextExtent, "Int", id, "Ptr", width, "Ptr", height, "Cdecl")
		}
	}
	class Player {
		static _getHealth := 0
		static _getArmor := 0
		static _getInteriorId := 0
		static _getCity := 0
		static _getDistrict := 0
		static _getPosition := 0
		static _getYaw := 0
		static _inInterior := 0
		static _inVehicle := 0
		static _isDriver := 0
		static _isFreezed := 0
        static _getLocalName := 0
		static _getLocalId := 0
		static _getNameById := 0
		static _getIdByName := 0
		static _getFullName := 0
		getHealth() {
			API._initialize()
			return DllCall(API.Player._getHealth, "Cdecl Int")
		}
		getArmor() {
			API._initialize()
			return DllCall(API.Player._getArmor, "Cdecl Int")
		}
		getInteriorId() {
			API._initialize()
			return DllCall(API.Player._getInteriorId, "Cdecl Int")
		}
		getCity(ByRef city, length) {
			API._initialize()
            VarSetCapacity(city, 2*length, 0)
			DllCall(API.Player._getCity, "WStr", city, "Int", length, "Cdecl")
		}
		getDistrict(ByRef district, length) {
			API._initialize()
            VarSetCapacity(district, 2*length, 0)
			DllCall(API.Player._getDistrict, "WStr", district, "Int", length, "Cdecl")
		}
		getPosition(ByRef x, ByRef y, ByRef z) {
			API._initialize()
			DllCall(API.Player._getPosition, "Ptr", x, "Ptr", y, "Ptr", z, "Cdecl")
		}
		getYaw() {
			API._initialize()
			return DllCall(API.Player._getYaw, "Cdecl Int")
		}
		inInterior() {
			API._initialize()
			return DllCall(API.Player._inInterior, "Cdecl Int")
		}
		inVehicle() {
			API._initialize()
			return DllCall(API.Player._inVehicle, "Cdecl Int")
		}
		isDriver() {
			API._initialize()
			return DllCall(API.Player._isDriver, "Cdecl Int")
		}
		isFreezed() {
			API._initialize()
			return DllCall(API.Player._isFreezed, "Cdecl Int")
		}
		getLocalName(ByRef name, length) {
			API._initialize()
            VarSetCapacity(name, 2*length, 0)
			DllCall(API.Player._getLocalName, "WStr", name, "Int", length, "Cdecl")
		}
		getLocalId() {
			API._initialize()
			return DllCall(API.Player._getLocalId, "Cdecl Int")
		}
		getNameById(id, ByRef name, length) {
			API._initialize()
            VarSetCapacity(name, 2*length, 0)
			DllCall(API.Player._getNameById, "Int", id, "WStr", name, "Int", length, "Cdecl")
		}
		getIdByName(name) {
			API._initialize()
			return DllCall(API.Player._getIdByName, "WStr", name, "Cdecl Int")
		}
		getFullName(name, ByRef fullName, length) {
			API._initialize()
            VarSetCapacity(fullName, 2*length, 0)
			DllCall(API.Player._getFullName, "WStr", name, "WStr", fullName, "Int", length, "Cdecl")
		}
	}
	class Vehicle {
		static _getSpeed := 0
		static _getHealth := 0
		static _getModelID := 0
		static _isLightActive := 0
		static _isLocked := 0
		static _isEngineRunning := 0
		static _useHorn := 0
		static _useSiren := 0
        static _getNumberplate := 0
		static _toggleSiren := 0
		getSpeed() {
			API._initialize()
			return DllCall(API.Vehicle._getSpeed, "Cdecl Int")
		}
		getHealth() {
			API._initialize()
			return DllCall(API.Vehicle._getHealth, "Cdecl Int")
		}
		getModelID() {
			API._initialize()
			return DllCall(API.Vehicle._getModelID, "Cdecl Int")
		}
		isLightActive() {
			API._initialize()
			return DllCall(API.Vehicle._isLightActive, "Cdecl Int")
		}
		isLocked() {
			API._initialize()
			return DllCall(API.Vehicle._isLocked, "Cdecl Int")
		}
		isEngineRunning() {
			API._initialize()
			return DllCall(API.Vehicle._isEngineRunning, "Cdecl Int")
		}
		useHorn() {
			API._initialize()
			return DllCall(API.Vehicle._useHorn, "Cdecl Int")
		}
		useSiren() {
			API._initialize()
			return DllCall(API.Vehicle._useSiren, "Cdecl Int")
		}
		getNumberplate(ByRef numberplate, length) {
			API._initialize()
            VarSetCapacity(numberplate, 2*length, 0)
			DllCall(API.Vehicle._getNumberplate, "WStr", numberplate, "Int", length, "Cdecl")
		}
		toggleSiren(state) {
			API._initialize()
			DllCall(API.Vehicle._toggleSiren, "Int", state, "Cdecl")
		}
	}
}