#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include <wx/stattext.h>
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Core/Component/controlComponent.hpp"
#include "labelMetaData.hpp"
class Label : public ControlComponent<wxStaticText> {
public:
    LabelMetaData * metaData;
    Label(LabelMetaData * metaData): ControlComponent(metaData->parent, metaData->componentID) {
        this->metaData = metaData;
        elementRef = new wxStaticText(
          ownerWindow,
          elementID,
          _(metaData->label),
          wxDefaultPosition,
          wxSize(metaData->width, metaData->height),
          0,
          metaData->componentID);
          elementRef->Wrap(metaData->width);
    }
};

#endif // LABEL_HPP_INCLUDED
