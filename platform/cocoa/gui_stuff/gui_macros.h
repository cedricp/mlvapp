/* Because why write out Objective-C code 100000000000s of times? */

/* Creates a slider + labels on the right sidebar */
#define CREATE_SLIDER_RIGHT( sliderName, labelName, valueLabelName, labelString, slotNumber, methodName, offset, defaultValueDouble ) \
 \
NSTextField * labelName = [ \
    [NSTextField alloc]  \
    initWithFrame: NSMakeRect( RIGHT_SIDEBAR_LABEL(slotNumber, ELEMENT_HEIGHT, offset) ) \
]; \
[labelName setLabelStyle]; /* From useful_methods.h */ \
/*[labelName setFont:[NSFont fontWithName:@"Helvetica" size:12.7]];*/ \
[labelName anchorTop: YES]; \
[labelName anchorRight: YES]; \
[labelName setStringValue: labelString]; \
[[window contentView] addSubview: labelName]; \
 \
NSTextField * valueLabelName = [ \
    [NSTextField alloc]  \
    initWithFrame: NSMakeRect( RIGHT_SIDEBAR_VALUE_LABEL(slotNumber, ELEMENT_HEIGHT, offset) ) \
]; \
[valueLabelName setLabelStyle]; /* From useful_methods.h */ \
[valueLabelName anchorTop: YES]; \
[valueLabelName anchorRight: YES]; \
[valueLabelName setStringValue: @"1.0"]; \
[[window contentView] addSubview: valueLabelName]; \
 \
NSSlider * sliderName = [ \
    [NSSlider alloc] \
    initWithFrame: NSMakeRect( RIGHT_SIDEBAR_SLIDER(slotNumber, ELEMENT_HEIGHT, offset) ) \
]; \
[sliderName setTarget: sliderName]; \
[sliderName setAction: @selector(methodName)]; \
[sliderName setDoubleValue: defaultValueDouble]; \
[sliderName anchorRight: YES]; \
[sliderName anchorTop: YES]; \
[[window contentView] addSubview: sliderName];

/* Adding more than 1 button causes segmentation fault 11. Something is broken. */

/* Creates an button on the left sidebar */
#define CREATE_BUTTON_LEFT_TOP( buttonName, slotNumber, methodName, offset, buttonText ) \
NSButton * buttonName = [ \
    [NSButton alloc] \
    initWithFrame: NSMakeRect( LEFT_SIDEBAR_ELEMENT_TOP(slotNumber, ELEMENT_HEIGHT, offset) ) \
]; \
[buttonName setTarget: buttonName]; \
[buttonName setAction: @selector(methodName)]; \
[buttonName setBezelStyle: NSRoundedBezelStyle]; \
[buttonName setTitle: buttonText]; \
[buttonName anchorLeft: YES]; \
[buttonName anchorTop: YES]; \
[[window contentView] addSubview: buttonName];


/* Creates an button on the left sidebar */
#define CREATE_BUTTON_LEFT_BOTTOM( buttonName, slotNumber, methodName, offset, buttonText ) \
NSButton * buttonName = [ \
    [NSButton alloc] \
    initWithFrame: NSMakeRect( LEFT_SIDEBAR_ELEMENT_BOTTOM(slotNumber, ELEMENT_HEIGHT, offset) ) \
]; \
[buttonName setTarget: buttonName]; \
[buttonName setAction: @selector(methodName)]; \
[buttonName setBezelStyle: NSRoundedBezelStyle]; \
[buttonName setTitle: buttonText]; \
[buttonName anchorLeft: YES]; \
[buttonName anchorBottom: YES]; \
[[window contentView] addSubview: buttonName];


/* Creates an button on the right sidebar */
#define CREATE_INPUT_WITH_LABEL_LEFT( inputName, slotNumber, methodName, offset, labelText ) \
NSTextField * inputName = [ \
    [NSTextField alloc] \
    initWithFrame: NSMakeRect( LEFT_SIDEBAR_ELEMENT_BOTTOM(slotNumber, 24, offset) ) \
]; \
[inputName setStringValue:@"2048"]; \
/*[inputName autorelease];*/ \
[inputName setTarget: inputName]; \
[inputName setAction: @selector(methodName)]; \
/*[inputName anchorLeft: YES]; \
[inputName anchorTop: YES];*/ \
[[window contentView] addSubview: inputName];