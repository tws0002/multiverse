//-*****************************************************************************
//
// Copyright (c) 2014,
//
// All rights reserved.
//
//-*****************************************************************************

#include <Alembic/AbcCoreGit/OrImpl.h>

namespace Alembic {
namespace AbcCoreGit {
namespace ALEMBIC_VERSION_NS {

//-*****************************************************************************
//-*****************************************************************************
// OBJECT READER IMPLEMENTATION
//-*****************************************************************************
//-*****************************************************************************

//-*****************************************************************************
// Reading as a child of a parent.
OrImpl::OrImpl( AbcA::ObjectReaderPtr iParent,
                GitGroupPtr iParentGroup,
                std::size_t iGroupIndex,
                ObjectHeaderPtr iHeader )
    : m_header( iHeader )
{
    m_parent = Alembic::Util::dynamic_pointer_cast< OrImpl,
        AbcA::ObjectReader > (iParent);

    // Check validity of all inputs.
    ABCA_ASSERT( m_parent, "Invalid parent in OrImpl(Object)" );
    ABCA_ASSERT( m_header, "Invalid header in OrImpl(Object)" );

    m_archive = m_parent->getArchiveImpl();
    ABCA_ASSERT( m_archive, "Invalid archive in OrImpl(Object)" );

#if 0
    StreamIDPtr streamId = m_archive->getStreamID();
    std::size_t id = streamId->getID();
#endif
    // NOTE: we could create groups for OrImpl by saving children names on write side
    // and reading back them from json
    TODO("create GitGroup and instantiate m_data");
#if 0
    GitGroupPtr group = iParentGroup->getGroup( iGroupIndex, false, id );
    m_data.reset( new OrData( group, iHeader->getFullName(), id,
        *m_archive, m_archive->getIndexedMetaData() ) );
#endif
}

//-*****************************************************************************
OrImpl::OrImpl( Alembic::Util::shared_ptr< ArImpl > iArchive,
                OrDataPtr iData,
                ObjectHeaderPtr iHeader )
    : m_archive( iArchive )
    , m_data( iData )
    , m_header( iHeader )
{

    ABCA_ASSERT( m_archive, "Invalid archive in OrImpl(Archive)" );
    ABCA_ASSERT( m_data, "Invalid data in OrImpl(Archive)" );
    ABCA_ASSERT( m_header, "Invalid header in OrImpl(Archive)" );
}

//-*****************************************************************************
OrImpl::~OrImpl()
{
    // Nothing.
}

//-*****************************************************************************
const AbcA::ObjectHeader & OrImpl::getHeader() const
{
    return *m_header;
}

//-*****************************************************************************
AbcA::ArchiveReaderPtr OrImpl::getArchive()
{
    return m_archive;
}

//-*****************************************************************************
AbcA::ObjectReaderPtr OrImpl::getParent()
{
    return m_parent;
}

//-*****************************************************************************
AbcA::CompoundPropertyReaderPtr OrImpl::getProperties()
{
    return m_data->getProperties( asObjectPtr() );
}

//-*****************************************************************************
size_t OrImpl::getNumChildren()
{
    return m_data->getNumChildren();
}

//-*****************************************************************************
const AbcA::ObjectHeader & OrImpl::getChildHeader( size_t i )
{
    return m_data->getChildHeader( asObjectPtr(), i );
}

//-*****************************************************************************
const AbcA::ObjectHeader * OrImpl::getChildHeader( const std::string &iName )
{
    return m_data->getChildHeader( asObjectPtr(), iName );
}

//-*****************************************************************************
AbcA::ObjectReaderPtr OrImpl::getChild( const std::string &iName )
{
    return m_data->getChild( asObjectPtr(), iName );
}

AbcA::ObjectReaderPtr OrImpl::getChild( size_t i )
{
    return m_data->getChild( asObjectPtr(), i );
}

//-*****************************************************************************
AbcA::ObjectReaderPtr OrImpl::asObjectPtr()
{
    return shared_from_this();
}

//-*****************************************************************************
bool OrImpl::getPropertiesHash( Util::Digest & oDigest )
{
    UNIMPLEMENTED("OrImpl::getPropertiesHash()");
#if 0
    StreamIDPtr streamId = m_archive->getStreamID();
    std::size_t id = streamId->getID();
    m_data->getPropertiesHash( oDigest, id );
    return true;
#endif
    return false;
}

//-*****************************************************************************
bool OrImpl::getChildrenHash( Util::Digest & oDigest )
{
    UNIMPLEMENTED("OrImpl::getChildrenHash()");
#if 0
    StreamIDPtr streamId = m_archive->getStreamID();
    std::size_t id = streamId->getID();
    m_data->getChildrenHash( oDigest, id );
    return true;
#endif
    return false;
}

//-*****************************************************************************
Alembic::Util::shared_ptr< ArImpl > OrImpl::getArchiveImpl() const
{
    return m_archive;
}

} // End namespace ALEMBIC_VERSION_NS
} // End namespace AbcCoreGit
} // End namespace Alembic