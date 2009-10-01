/*
 * Copyright (c) 1996-2009 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/************************************************************************
 * $Id: Object.h,v 1.20 2008/06/23 18:45:48 legendre Exp $
 * Object.h: interface to objects, symbols, lines and instructions.
************************************************************************/


#if !defined(_Object_h_)
#define _Object_h_
/************************************************************************
 * header files.
************************************************************************/

// trace data streams
#include <string>
#include <vector>

#include "Symbol.h"
#include "LineInformation.h"
#include "common/h/headers.h"
#include "common/h/MappedFile.h"
#include "common/h/lprintf.h"

namespace Dyninst{
namespace SymtabAPI{

extern bool symbol_compare(const Symbol *s1, const Symbol *s2);

class Symtab;
class Region;
class ExceptionBlock;
class relocationEntry;

const char WILDCARD_CHARACTER = '?';
const char MULTIPLE_WILDCARD_CHARACTER = '*';

/************************************************************************
 * class AObject
 *
 *  WHAT IS THIS CLASS????  COMMENTS????
 *  Looks like it has a dictionary hash of symbols, as well as
 *   a ptr to to the code section, an offset into the code section,
 *   and a length of the code section, and ditto for the data
 *   section....
************************************************************************/

class MemRegReader;

class AObject {
public:
    SYMTAB_EXPORT AObject() {};
    SYMTAB_EXPORT unsigned nsymbols () const;
    
    SYMTAB_EXPORT bool get_symbols( std::string & name, std::vector< Symbol *> & symbols);

    SYMTAB_EXPORT char*       code_ptr () const; 
    SYMTAB_EXPORT Offset           code_off () const;
    SYMTAB_EXPORT Offset           code_len () const;

    SYMTAB_EXPORT char*       data_ptr () const;
    SYMTAB_EXPORT Offset           data_off () const;
    SYMTAB_EXPORT Offset           data_len () const;

    SYMTAB_EXPORT bool 	      is_aout  () const;
    SYMTAB_EXPORT bool        isDynamic() const;

    SYMTAB_EXPORT unsigned	      no_of_sections () const;
    SYMTAB_EXPORT unsigned	      no_of_symbols  ()	const;

    SYMTAB_EXPORT bool getAllExceptions(std::vector<ExceptionBlock *>&excpBlocks) const;
    SYMTAB_EXPORT std::vector<Region *> getAllRegions() const;

    SYMTAB_EXPORT supportedLanguages pickLanguage(std::string &working_module, char *working_options,
                                                                    supportedLanguages working_lang);

    SYMTAB_EXPORT Offset loader_off() const;
    SYMTAB_EXPORT unsigned loader_len() const;
    SYMTAB_EXPORT int getAddressWidth() const;

    bool isStaticBinary() const {return is_static_binary_;}

    SYMTAB_EXPORT virtual char *  mem_image() const;

    SYMTAB_EXPORT virtual  bool   needs_function_binding()  const;
    SYMTAB_EXPORT virtual  bool   get_func_binding_table(std::vector<relocationEntry> &) const;
    SYMTAB_EXPORT virtual  bool   get_func_binding_table_ptr(const std::vector<relocationEntry> *&) const; 
    SYMTAB_EXPORT virtual  bool   addRelocationEntry(relocationEntry &re);
    SYMTAB_EXPORT bool   getSegments(std::vector<Segment> &segs) const;

    SYMTAB_EXPORT bool have_deferred_parsing( void ) const;
    // for debuggering....
    SYMTAB_EXPORT const std::ostream &dump_state_info(std::ostream &s);

    SYMTAB_EXPORT void * getErrFunc() const;
    SYMTAB_EXPORT dyn_hash_map< std::string, std::vector< Symbol *> > *getAllSymbols();
    SYMTAB_EXPORT MappedFile *getMappedFileForDebugInfo() { return mfForDebugInfo; }
    
    SYMTAB_EXPORT virtual bool hasFrameDebugInfo() {return false;}
    SYMTAB_EXPORT virtual bool getRegValueAtFrame(Address /*pc*/,
                                                  Dyninst::MachRegister /*reg*/, 
                                                  Dyninst::MachRegisterVal & /*reg_result*/,
                                                  MemRegReader * /*reader*/) {return false;}
    
    SYMTAB_EXPORT const std::string findModuleForSym(Symbol *sym);
    SYMTAB_EXPORT void clearSymsToMods();
    SYMTAB_EXPORT bool hasError() const;

    SYMTAB_EXPORT SymtabError getLastError() { return serr_; }

protected:
    SYMTAB_EXPORT virtual ~AObject();
    // explicitly protected
    SYMTAB_EXPORT AObject(MappedFile * , MappedFile *, void (*err_func)(const char *));
    SYMTAB_EXPORT AObject(MappedFile * , MappedFile *, 
                      dyn_hash_map<std::string, LineInformation> &, 
                      void (*)(const char *)) { assert(0); }
    SYMTAB_EXPORT AObject(const AObject &obj);

    MappedFile *mf;
    MappedFile *mfForDebugInfo;

    std::vector< Region *> regions_;

    dyn_hash_map< std::string, std::vector< Symbol *> > symbols_;
	std::map< Symbol *, std::string > symsToModules_;
    dyn_hash_map<Offset, std::vector<Symbol *> > symsByOffset_;
    std::vector<std::pair<std::string, Offset> > modules_;

    char*   code_ptr_;
    Offset code_off_;
    Offset code_len_;

    char*   data_ptr_;
    Offset data_off_;
    Offset data_len_;

    Offset code_vldS_;
    Offset code_vldE_;

    Offset data_vldS_;
    Offset data_vldE_;

    Offset loader_off_; //only used on aix right now.  could be
    Offset loader_len_; //needed on other platforms in the future

//    Offset loadAddress_;
//    Offset entryAddress_;
//    Offset baseAddress_;
 
    SymtabError serr_;

    bool is_aout_;
    bool is_dynamic_;
    bool has_error;

    bool is_static_binary_;

    unsigned no_of_sections_;
    unsigned no_of_symbols_;

    bool deferredParse;
    void (*err_func_)(const char*);
    int addressWidth_nbytes;

    std::vector<ExceptionBlock> catch_addrs_; //Addresses of C++ try/catch blocks;
    
private:
    friend class SymbolIter;
    friend class Symtab;

};

}//namepsace Symtab
}//namespace Dyninst

/************************************************************************
 * include the architecture-operating system specific object files.
************************************************************************/

#if defined(os_solaris) || defined(os_linux) || defined(os_bg_ion)
#include "Object-elf.h"
#elif defined(os_aix)
#include "Object-xcoff.h"
#elif defined(os_windows)
#include "Object-nt.h"
#elif defined(os_osf)
#include "Object-coff.h"
#else
#error "unknown platform"
#endif

/************************************************************************
 * class SymbolIter
************************************************************************/

namespace Dyninst{
namespace SymtabAPI{

class SymbolIter {
 private:
   dyn_hash_map< std::string, std::vector< Symbol *> > *symbols;
   unsigned int currentPositionInVector;
   dyn_hash_map< std::string, std::vector< Symbol *> >::iterator symbolIterator;
   
 public:
   SymbolIter( Object & obj );
   SymbolIter( const SymbolIter & src );
   ~SymbolIter ();
   
   void reset ();
   
   operator bool() const;
   void operator++ ( int );
   const std::string & currkey() const;
   
   /* If it's important that this be const, we could try to initialize
      currentVector to '& symbolIterator.currval()' in the constructor. */
   Symbol *currval();
   
 private:	
   
   SymbolIter & operator = ( const SymbolIter & ); // explicitly disallowed
}; /* end class SymbolIter() */

}//namepsace SymtabAPI
}//namespace Dyninst

#endif /* !defined(_Object_h_) */
