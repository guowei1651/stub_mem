#! /bin/python

import sys
import os
import re

def usage(argv):
    print "usage:"
    print "%s  filename objname rootpath sourcepath" %argv

def readFile(file):
  str = ""
  f = open(file)
  try:
      for line in f:
        str += line
  finally:
      f.close()
  
  return str

def writeFile(file,str):
  f = open(file,'w')
  try:
    f.write(str)
  finally:
    f.close()

def delAllStubMEM(str, delStr):
  while True:
    m = re.search(delStr,str)
    if m is None :
      break;
    s = m.group()
    str = str.replace("\n"+s+"\n","")
  return str

def checkIF0Comment(str,includeFile):
  #regularStr = "\#if\s*0(.|\s)*?\\" + includeFile + "(.|\s)*?\#endif"
  regularStr = "\#if\s*0.*?\\" + includeFile + ".*?\#endif"
  print regularStr
  m = re.search(regularStr, str, re.MULTILINE|re.DOTALL)
  if m is not None:
    #print m.group()
    return m.end()
  else:
    return -1

def checkSlashComment(str,includeFile):
  #regularStr = "\/\*(.|\s)*?\\"+includeFile+"(.|\s)*?\*\/"
  regularStr = "(\/\*)1.*?\\"+includeFile+".*?(\*\/)1"
  print regularStr
  m = re.search(regularStr, str, re.MULTILINE|re.DOTALL)
  if m is not None:
    #print m.group()
    return m.end()
  else:
    return -1

def addInclude(file, objname):
  str = readFile(file)

  str = delAllStubMEM(str,'\#include (")stub_mem.*\.h(")')
  
  index=str.rfind("#include")
  index=str.find("\n",index)

  includeFile = "#include \"stub_mem"+objname+".h\"";

  reslut = str[0:index]+"\n"+ includeFile +"\n"+ str[index:]

  endIndex = checkSlashComment(reslut, includeFile)
  print endIndex
  if endIndex != -1:
    endIndex = endIndex - (len(includeFile)+2)
    reslut = delAllStubMEM(reslut,'\#include (")stub_mem.*\.h(")')
    reslut = reslut[0:endIndex]+"\n"+ includeFile +"\n"+ reslut[endIndex:]

  endIndex = checkIF0Comment(reslut, includeFile)
  print endIndex
  if endIndex != -1:
    endIndex = endIndex - (len(includeFile)+2)
    reslut = delAllStubMEM(reslut,'\#include (")stub_mem.*\.h(")')
    reslut = reslut[0:endIndex]+"\n"+ includeFile +"\n"+ reslut[endIndex:]

  writeFile(file,reslut)

def stub(rootpath, sourcpath, file, objname):
  file = rootpath+"/pub/"+file
  str = readFile(file)

  reslut = str.replace("_VERSION_NAME # ", objname)
  #print "stub"
  #print sourcpath+"/"+os.path.basename(file)
  
  writeFile(sourcpath+"/"+os.path.basename(file),reslut)

def createH(path, file, objname):
  str = readFile(path + file)
  
  reslut = str.replace("_VERSION_NAME # ", objname)

  file = path + "/pub/stub_mem" + objname + ".h"
  #print file
  writeFile(file,reslut)

if __name__ == '__main__':
  if len(sys.argv) < 5 :
    usage(sys.argv)
    sys.exit(0)

  if sys.argv[1].find("stub_mem.c") == -1:
    file = sys.argv[3] + "/pub/stub_mem" + sys.argv[2] + ".h"
    if os.path.exists(file) :
      #print "exists"
      None
    else :
      createH(sys.argv[3],"/pub/stub_mem.h",sys.argv[2])

    addInclude(sys.argv[1], sys.argv[2])

  else :
    stub(sys.argv[3],sys.argv[4],"stub_mem.c", sys.argv[2])
