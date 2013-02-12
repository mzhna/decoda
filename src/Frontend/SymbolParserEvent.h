/*

Decoda
Copyright (C) 2007-2013 Unknown Worlds Entertainment, Inc. 

This file is part of Decoda.

Decoda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Decoda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Decoda.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef SYMBOL_PARSER_EVENT_H
#define SYMBOL_PARSER_EVENT_H

#include <wx/wx.h>
#include <wx/event.h>
#include <vector>

//
// Forward declarations.
//

class Symbol;

//
// Event definitions.
//

DECLARE_EVENT_TYPE(wxEVT_SYMBOL_PARSER_EVENT, -1)

/**
 * Class for events sent by the symbol parser thread. This doesn't really handle
 * management of the memory for the symbols array in a very good way since it assumes
 * the event is handled by exactly one handler, but should be good enough for our
 * purposes.
 */
class SymbolParserEvent : public wxEvent
{

public:

    /**
     * Constructor.
     */
    SymbolParserEvent(unsigned int fileId, const std::vector<Symbol*>& symbols);
    
    /**
     * From wxEvent.
     */
    virtual wxEvent* Clone() const;

    /**
     * Gets the id of the file that the symbols pertain to.
     */
    unsigned int GetFileId() const;

    /**
     * Gets the symbols for the file.
     */
    const std::vector<Symbol*>& GetSymbols() const;

private:

    unsigned int            m_fileId;
    std::vector<Symbol*>    m_symbols;

};

typedef void (wxEvtHandler::*SymbolParserEventFunction)(SymbolParserEvent&);

#define EVT_SYMBOL_PARSER(fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_SYMBOL_PARSER_EVENT, 0, -1, \
    (wxObjectEventFunction) (wxEventFunction) wxStaticCastEvent( SymbolParserEventFunction, & fn ), (wxObject *) NULL ),

#endif