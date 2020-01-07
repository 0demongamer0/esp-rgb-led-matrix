/* MIT License
 *
 * Copyright (c) 2019 - 2020 Andreas Merkle <web@blue-andi.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
 * @brief  Progress bar
 * @author Andreas Merkle <web@blue-andi.de>
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "ProgressBar.h"

/******************************************************************************
 * Compiler Switches
 *****************************************************************************/

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and classes
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/

/* Initialize text widget type. */
const char* ProgressBar::WIDGET_TYPE = "progressBar";

/******************************************************************************
 * Public Methods
 *****************************************************************************/

void ProgressBar::update(IGfx& gfx)
{
    switch(m_algorithm)
    {
    case ALGORITHM_PIXEL_WISE:
        showProgressPixel(gfx);
        break;

    case ALGORITHM_PROGRESS_BAR:
        showProgressBar(gfx);
        break;

    case ALGORITHM_MAX:
        /* Should never happen. */
        break;

    default:
        /* Should never happen. */
        break;
    }

    return;
}

/******************************************************************************
 * Protected Methods
 *****************************************************************************/

/******************************************************************************
 * Private Methods
 *****************************************************************************/

void ProgressBar::showProgressPixel(IGfx& gfx)
{
    int16_t pixelCount  = gfx.width() * gfx.height() * m_progress / 100u;
    int16_t x           = 0;
    int16_t y           = 0;

    while((0 < pixelCount) && (gfx.height() > y))
    {
        gfx.drawPixel(x, y, m_color.to565());
        
        --pixelCount;
        
        ++x;
        if (gfx.width() <= x)
        {
            x = 0;
            ++y;
        }
    }

    return;
}

void ProgressBar::showProgressBar(IGfx& gfx)
{
    int16_t index = 0u;

    if (gfx.width() > gfx.height())
    {
        int16_t maxX = (gfx.width() * m_progress) / 100;

        for(index = 0; index < maxX; ++index)
        {
            gfx.drawLine(index, 0, index, gfx.height() - 1, m_color.to565());
        }
    }
    else
    {
        int16_t maxY = (gfx.width() * m_progress) / 100;

        for(index = 0; index < maxY; ++index)
        {
            gfx.drawLine(0, index, gfx.width() - 1, index, m_color.to565());
        }
    }

    return;
}

/******************************************************************************
 * External Functions
 *****************************************************************************/

/******************************************************************************
 * Local Functions
 *****************************************************************************/
