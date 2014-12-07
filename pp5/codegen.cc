/* File: codegen.cc
 * ----------------
 * Implementation for the CodeGenerator class. The methods don't do anything
 * too fancy, mostly just create objects of the various Tac instruction
 * classes and append them to the list.

 top secret code = 6D61474

 */

#include "codegen.h"
#include <string.h>
#include "tac.h"
#include "mips.h"

Location* CodeGenerator::ThisPtr= new Location(fpRelative, 4, "this");

/***************************************************************************/
/***************************************************************************/

Location* CodeGenerator::getCurrentInstance() {
  return current_this_ptr;
}

void CodeGenerator::setCurrentInstance(Location *loc) {
  current_this_ptr = loc;
}

ClassDecl* CodeGenerator::findClassDecl(char *name) {
  return programPtr ? programPtr->findClassDecl(name) : NULL;
}

FnDecl* CodeGenerator::findFnDecl(char *name) {
  return programPtr ? programPtr->findFnDecl(name) : NULL;
}

char* CodeGenerator::getCurrentBreakLabel() {
  return currentBreakLabel;
}

void CodeGenerator::setCurrentBreakLabel(char *label) {
  currentBreakLabel = label;
}

Decl* CodeGenerator::findGlobal(char *name) {
  return globaltable->Lookup(name);
}

void CodeGenerator::storeGlobalFnDecl(FnDecl *fnDecl) {
  globalFnTable->Enter(fnDecl->getName(), fnDecl);
}

FnDecl* CodeGenerator::findGlobalFnDecl(Identifier *identifier) {
  return programPtr->findFnDecl(identifier->getName());
  //return globalFnTable->Lookup(identifier->getName());
}

/***************************************************************************/
/***************************************************************************/

CodeGenerator::CodeGenerator()
{
  //spaceForTemps = 0;
  char* currentBreakLabel = NULL;
  //mainHasBeenDefined = false;
  globaltable = new Hashtable<Decl*>;
  globalFnTable = new Hashtable<FnDecl*>;
  TempNumber = 0;
}

char *CodeGenerator::NewLabel()
{
  static int nextLabelNum = 0;
  char temp[10];
  sprintf(temp, "_L%d", nextLabelNum++);
  return strdup(temp);
}

Location *CodeGenerator::GenGlobalVar(char *name, VarDecl *varDecl)
{
  //printf("generating: %s\n", name);
  static int nextGlobalNum;
  Location *result = new Location(gpRelative, (4 * nextGlobalNum), name);
  nextGlobalNum++;
  Assert(result != NULL);
  globaltable->Enter(name, varDecl);
  return result;
}

// keep track of the temp + local variables (assign locations + set frame size with the TempNumber var)
int CodeGenerator::IncrementTempNumber() {
  return TempNumber++;
}

int CodeGenerator::GetTempNumber() {
  return TempNumber;
}

void CodeGenerator::ResetTempNumber() {
  TempNumber = 0;
}

Location *CodeGenerator::GenLocalVar(char *name)
{
  static int nextLocalNum;
  Location *result = new Location(fpRelative, -8 - (4 * IncrementTempNumber()), name);
  //printf("gen local var"); result->print();
  nextLocalNum++;
  Assert(result != NULL);
  return result;
}

//Location(Segment seg, int offset, const char *name); (reference)
Location *CodeGenerator::GenTempVar()
{
  static int nextTempNum;
  char temp[10];
  Location *result = NULL;
  sprintf(temp, "_tmp%d", nextTempNum++);
  //printf("temp num %s at %i\n", temp, nextTempNum);
  result = new Location(fpRelative, -8 - (4 * IncrementTempNumber()), temp);
  Assert(result != NULL);
  return result;
}

Location *CodeGenerator::CustomGenLocalVar(char *name, int next_local_num)
{
  //printf("local num %i\n", nextLocalNum);
  Location *result = new Location(fpRelative, -8 - (4 * next_local_num), name);
  //printf("gen local var"); result->print();
  Assert(result != NULL);
  return result;
}
 
Location *CodeGenerator::GenLoadConstant(int value)
{
  Location *result = GenTempVar();
  code.push_back(new LoadConstant(result, value));
  return result;
}

Location *CodeGenerator::GenLoadConstant(const char *s)
{
  Location *result = GenTempVar();
  code.push_back(new LoadStringConstant(result, s));
  return result;
} 

Location *CodeGenerator::GenLoadLabel(const char *label)
{
  Location *result = GenTempVar();
  code.push_back(new LoadLabel(result, label));
  return result;
} 


void CodeGenerator::GenAssign(Location *dst, Location *src)
{
  code.push_back(new Assign(dst, src));
}


Location *CodeGenerator::GenLoad(Location *ref, int offset)
{
  Location *result = GenTempVar();
  code.push_back(new Load(result, ref, offset));
  return result;
}

void CodeGenerator::GenStore(Location *dst,Location *src, int offset)
{
  code.push_back(new Store(dst, src, offset));
}


Location *CodeGenerator::GenBinaryOp(const char *opName, Location *op1, Location *op2)
{
  Location *result = GenTempVar();
  code.push_back(new BinaryOp(BinaryOp::OpCodeForName(opName), result, op1, op2));
  return result;
}


void CodeGenerator::GenLabel(const char *label)
{
  code.push_back(new Label(label));
}

void CodeGenerator::GenIfZ(Location *test, const char *label)
{
  code.push_back(new IfZ(test, label));
}

void CodeGenerator::GenGoto(const char *label)
{
  code.push_back(new Goto(label));
}

void CodeGenerator::GenReturn(Location *val)
{
  code.push_back(new Return(val));
}


BeginFunc *CodeGenerator::GenBeginFunc()
{
  BeginFunc *result = new BeginFunc;
  code.push_back(result);
  return result;
}

void CodeGenerator::GenEndFunc()
{
  code.push_back(new EndFunc());
}

void CodeGenerator::GenPushParam(Location *param)
{
  code.push_back(new PushParam(param));
}

void CodeGenerator::GenPopParams(int numBytesOfParams)
{
  Assert(numBytesOfParams >= 0 && numBytesOfParams % VarSize == 0); // sanity check
  if (numBytesOfParams > 0)
    code.push_back(new PopParams(numBytesOfParams));
}

Location *CodeGenerator::GenLCall(const char *label, bool fnHasReturnValue)
{
  Location *result = fnHasReturnValue ? GenTempVar() : NULL;
  code.push_back(new LCall(label, result));
  return result;
}

Location *CodeGenerator::GenACall(Location *fnAddr, bool fnHasReturnValue)
{
  Location *result = fnHasReturnValue ? GenTempVar() : NULL;
  code.push_back(new ACall(fnAddr, result));
  return result;
}
 
 
static struct _builtin {
  const char *label;
  int numArgs;
  bool hasReturn;
} builtins[] =
 {{"_Alloc", 1, true},
  {"_ReadLine", 0, true},
  {"_ReadInteger", 0, true},
  {"_StringEqual", 2, true},
  {"_PrintInt", 1, false},
  {"_PrintString", 1, false},
  {"_PrintBool", 1, false},
  {"_Halt", 0, false}};

Location *CodeGenerator::GenBuiltInCall(BuiltIn bn,Location *arg1, Location *arg2)
{
  Assert(bn >= 0 && bn < NumBuiltIns);
  struct _builtin *b = &builtins[bn];
  Location *result = NULL;

  if (b->hasReturn) result = GenTempVar();
                // verify appropriate number of non-NULL arguments given
  Assert((b->numArgs == 0 && !arg1 && !arg2)
	|| (b->numArgs == 1 && arg1 && !arg2)
	|| (b->numArgs == 2 && arg1 && arg2));
  if (arg2) code.push_back(new PushParam(arg2));
  if (arg1) code.push_back(new PushParam(arg1));
  code.push_back(new LCall(b->label, result));
  GenPopParams(VarSize*b->numArgs);
  return result;
}


void CodeGenerator::GenVTable(const char *className, List<const char *> *methodLabels)
{
  code.push_back(new VTable(className, methodLabels));
}


void CodeGenerator::DoFinalCodeGen()
{
  if (IsDebugOn("tac")) { // if debug don't translate to mips, just print Tac
    std::list<Instruction*>::iterator p;
    for (p= code.begin(); p != code.end(); ++p) {
      (*p)->Print();
    }
   }  else {
     Mips mips;
     mips.EmitPreamble();

    std::list<Instruction*>::iterator p;
    for (p= code.begin(); p != code.end(); ++p) {
      (*p)->Emit(&mips);
    }
  }
}


