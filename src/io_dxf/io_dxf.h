/****************************************************************************
** Copyright (c) 2021, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#pragma once

#include "../base/io_reader.h"
#include "../base/io_single_format_factory.h"

#include <TopoDS_Shape.hxx>
#include <string>

namespace Mayo::IO {

// Reader for DXF file format based on FreeCad's CDxfRead
class DxfReader : public Reader {
public:
    ~DxfReader();

    bool readFile(const FilePath& filepath, TaskProgress* progress) override;
    TDF_LabelSequence transfer(DocumentPtr doc, TaskProgress* progress) override;

    struct Parameters {
        bool importAnnotations = true;
        bool groupLayers = true;
        std::string fontNameForTextObjects = "Arial";
        // TODO
        //     Add syncAttribs option? If ON the reader creates missing ATTRIBs from ATTDEF
        //     Or mode-like:
        //         * "strict" -> no creation of missing ATTRIBs
        //         * "sync" -> creates missing ATTRIBs from ATTDEF
        //         * "diagnose" -> no creation but lists "incomplete" INSERTs regarding ATTDEF
    };
    Parameters& parameters() { return m_params; }
    const Parameters& constParameters() const { return m_params; }

    static std::unique_ptr<PropertyGroup> createProperties(PropertyGroup* parentGroup);
    void applyProperties(const PropertyGroup* params) override;

private:
    class Properties;
    class ReaderImpl;

    Parameters m_params;
    ReaderImpl* m_impl = nullptr;
};

// Provides factory to create DxfReader objects
class DxfFactoryReader : public SingleFormatFactoryReader<Format_DXF, DxfReader> {};

} // namespace Mayo::IO
