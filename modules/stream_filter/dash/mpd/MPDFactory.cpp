/*
 * MPDFactory.cpp
 *****************************************************************************
 * Copyright (C) 2010 - 2012 Klagenfurt University
 *
 * Created on: Jan 27, 2012
 * Authors: Christopher Mueller <christopher.mueller@itec.uni-klu.ac.at>
 *          Christian Timmerer  <christian.timmerer@itec.uni-klu.ac.at>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "MPDFactory.h"

using namespace dash::xml;
using namespace dash::mpd;

MPD* MPDFactory::create             (dash::xml::Node *root, stream_t *p_stream, Profile profile)
{
    IMPDParser *parser = NULL;

    switch( profile )
    {
        case Profile::Full:
            parser = new BasicCMParser(root, p_stream);
            break;
        case Profile::ISOOnDemand:
        case Profile::ISOMain:
            parser = new IsoffMainParser(root, p_stream);
        default:
            break;
    }

    if(!parser)
        return NULL;

    MPD* mpd = NULL;
    if(parser->parse())
        mpd = parser->getMPD();

    delete parser;

    if (mpd)
        mpd->setProfile(profile);

    return mpd;
}
