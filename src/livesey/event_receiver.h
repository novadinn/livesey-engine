#ifndef EVENT_RECEIVER_H
#define EVENT_RECEIVER_H

#include "events.h"

namespace Livesey {
    
    struct EventReceiver {
	virtual ~EventReceiver() = default;
	
	virtual void onCreate() {}
	virtual void onUpdate() {}
	virtual void onDraw() {}
	virtual void onDestroy() {}

	virtual void onKeyEvent(const KeyEvent& e) {}
	virtual void onCharEvent(const CharEvent& e) {}
	virtual void onCursorPosEvent(const CursorPosEvent& e) {}
	virtual void onCursorEnterEvent(const CursorEnterEvent& e) {}
	virtual void onMouseButtonEvent(const MouseButtonEvent& e) {}
	virtual void onScrollEvent(const ScrollEvent& e) {}
	virtual void onCloseEvent(const CloseEvent& e) {}
	virtual void onSizeEvent(const SizeEvent& e) {}
	virtual void onFramebufferSizeEvent(const FramebufferSizeEvent& e) {}
	virtual void onContentScaleEvent(const ContentScaleEvent& e) {}
	virtual void onPosEvent(const PosEvent& e) {}
	virtual void onIconifyEvent(const IconifyEvent& e) {}
	virtual void onMaximizeEvent(const MaximizeEvent& e) {}
	virtual void onFocusEvent(const FocusEvent& e) {}
	virtual void onRefreshEvent(const RefreshEvent& e) {}
    };
}
   
#endif // EVENT_RECEIVER_H
