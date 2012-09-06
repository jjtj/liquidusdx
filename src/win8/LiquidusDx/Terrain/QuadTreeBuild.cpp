#include "pch.h"
#include "QuadTreeBuild.h"


using namespace Windows::Data::Json;

Quad* quad_tree_build(JsonArray^ arr)
{
  auto q = new Quad(
    (int)arr->GetNumberAt(0),
    (int)arr->GetNumberAt(1),
    (int)arr->GetNumberAt(2),
    (int)arr->GetNumberAt(3)
    );
  
  try
  {
    auto v = arr->GetAt(5);
    switch(v->ValueType) {
    case JsonValueType::Array:
      {
        auto childs = v->GetArray();
        auto childSize = childs->Size;
        for(unsigned int i=0;i<childSize;++i) {
          auto c = quad_tree_build(childs->GetArrayAt(i));
          q->AddChild(c);
        }
      }
      break;
    case JsonValueType::Null:
      ::OutputDebugString(L"NULL Json value found\r\n");
      break;
    }
  }
  catch (Platform::COMException^ ex)
  {
    // This one has no child.
    // Let's skip any addition.
    auto msg = ex->Message;
#if defined(_DEBUG)
    ::OutputDebugString(msg->Data());
#endif
  }
  

  return q;
}