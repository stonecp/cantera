#ifndef CXX_IDEALGASMIX
#define CXX_IDEALGASMIX

#include <string>

#include "kernel/IdealGasPhase.h"
#include "kernel/GRI_30_Kinetics.h"
#include "kernel/importCTML.h"

namespace Cantera {

    class GRI30 : 
        public IdealGasPhase, public GRI_30_Kinetics
    {
    public:
        GRI30() : m_ok(false), m_r(0) {
            string path = findInputFile("gri30.xml");
            ifstream fin(path.c_str());
            if (!fin) {
                throw CanteraError("GRI30","could not open "
                    +path+" for reading.");
            }
            
            m_r = new XML_Node("-");
            m_r->build(fin);
            m_ok = buildSolutionFromXML(*m_r, "gri30_hw", "phase", this, this);
            if (!m_ok) throw CanteraError("GRI30",
                "buildSolutionFromXML returned false");
        }


        virtual ~GRI30() {}

        bool operator!() { return !m_ok;}
        bool ready() { return m_ok; }
        friend ostream& operator<<(ostream& s, GRI30& mix) {
            string r = report(mix, true);
            s << r;
            return s;
        }

    protected:
        bool m_ok;
        XML_Node* m_r;

    private:
    };
}


#endif
