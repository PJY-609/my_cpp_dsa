#pragma once

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)

#define FromParentTo(x) ( IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))