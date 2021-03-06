
//////////////////////////////////////////////////////////////
//
// Header file for ReqMngFormClassUI
//
//    This file is generated by RapidApp 1.2
//
//    This class implements the user interface portion of a class
//    Normally it is not used directly.
//    Instead the subclass, ReqMngFormClass is instantiated
//
//    To extend or alter the behavior of this class, you should
//    modify the ReqMngFormClass files
//
//    Restrict changes to those sections between
//    the "//--- Start/End editable code block" markers
//
//    This will allow RapidApp to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//
//////////////////////////////////////////////////////////////
#ifndef REQMNGFORMCLASSUI_H
#define REQMNGFORMCLASSUI_H
#include <Vk/VkComponent.h>


//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations


class ReqMngFormClassUI : public VkComponent
{ 

  public:

    ReqMngFormClassUI ( const char *, Widget );
    ReqMngFormClassUI ( const char * );
    ~ReqMngFormClassUI();
    void create ( Widget );
    const char *  className();

    //---- Start editable code block: ReqMngFormClass public


    //---- End editable code block: ReqMngFormClass public


  protected:


    // Widgets created by this class

    Widget  _button43;
    Widget  _button45;
    Widget  _label29;
    Widget  _reqEntriesList;
    Widget  _reqMngFormClass1;
    Widget  _scrolledWindow6;


    // These virtual functions are called from the private callbacks (below)
    // Intended to be overriden in derived classes to define actions

    virtual void addReq ( Widget, XtPointer );
    virtual void browseSel ( Widget, XtPointer );
    virtual void delReq ( Widget, XtPointer );
    virtual void dfltAction ( Widget, XtPointer );
    virtual void extSel ( Widget, XtPointer );
    virtual void multSel ( Widget, XtPointer );
    virtual void singleSel ( Widget, XtPointer );

    //---- Start editable code block: ReqMngFormClass protected


    //---- End editable code block: ReqMngFormClass protected


  private: 

    // Array of default resources

    static String      _defaultReqMngFormClassUIResources[];


    // Callbacks to interface with Motif

    static void addReqCallback ( Widget, XtPointer, XtPointer );
    static void browseSelCallback ( Widget, XtPointer, XtPointer );
    static void delReqCallback ( Widget, XtPointer, XtPointer );
    static void dfltActionCallback ( Widget, XtPointer, XtPointer );
    static void extSelCallback ( Widget, XtPointer, XtPointer );
    static void multSelCallback ( Widget, XtPointer, XtPointer );
    static void singleSelCallback ( Widget, XtPointer, XtPointer );

    //---- Start editable code block: ReqMngFormClass private


    //---- End editable code block: ReqMngFormClass private
};
//---- Start editable code block: End of generated code


//---- End editable code block: End of generated code

#endif

