#ifndef PROGRESS_BAR
#define PROGRESS_BAR

#include "STD_TYPES.h"

/**
 * The function initializes a progress bar by displaying special characters on an LCD screen.
 */
void ProgressBar_init(void);

/**
 * The ProgressBar function displays a progress bar on an LCD screen based on the maximum value and
 * current value provided.
 * 
 * @param MaximumValue The MaximumValue parameter represents the maximum value that the progress bar
 * can reach. It is used to calculate the width of the progress bar based on the CurrentValue
 * parameter.
 * @param CurrentValue The CurrentValue parameter represents the current value of the progress bar. It
 * indicates how much progress has been made towards the maximum value.
 * @param LineNumber The LineNumber parameter represents the line number on which the progress bar will
 * be displayed.
 * 
 * @return The function does not have a return type, so it does not return any value.
 */

void ProgressBar(uint32 MaximumValue, uint32 CurrentValue, uint8 LineNumber);

#endif