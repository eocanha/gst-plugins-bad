/*
 * Microsoft Smooth-Streaming fragment parsing library
 *
 * gstmssfragmentparser.h
 *
 * Copyright (C) 2015 Igalia S.L
 * Copyright (C) 2015 Metrological
 *   Author: Philippe Normand <philn@igalia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library (COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GST_MSS_FRAGMENT_PARSER_H__
#define __GST_MSS_FRAGMENT_PARSER_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_MSS_FRAGMENT_FOURCC_MOOF GST_MAKE_FOURCC('m','o','o','f')
#define GST_MSS_FRAGMENT_FOURCC_MFHD GST_MAKE_FOURCC('m','f','h','d')
#define GST_MSS_FRAGMENT_FOURCC_TRAF GST_MAKE_FOURCC('t','r','a','f')
#define GST_MSS_FRAGMENT_FOURCC_TFHD GST_MAKE_FOURCC('t','f','h','d')
#define GST_MSS_FRAGMENT_FOURCC_TRUN GST_MAKE_FOURCC('t','r','u','n')
#define GST_MSS_FRAGMENT_FOURCC_UUID GST_MAKE_FOURCC('u','u','i','d')
#define GST_MSS_FRAGMENT_FOURCC_MDAT GST_MAKE_FOURCC('m','d','a','t')

typedef struct _GstTfxdBox
{
  guint8 version;
  guint32 flags;

  guint64 time;
  guint64 duration;
} GstTfxdBox;

typedef struct _GstTfrfBoxEntry
{
  guint64 time;
  guint64 duration;
} GstTfrfBoxEntry;

typedef struct _GstTfrfBox
{
  guint8 version;
  guint32 flags;

  gint entries_count;
  GstTfrfBoxEntry *entries;
} GstTfrfBox;

typedef enum _GstFragmentHeaderParserStatus
{
  GST_MSS_FRAGMENT_HEADER_PARSER_INIT,
  GST_MSS_FRAGMENT_HEADER_PARSER_FINISHED
} GstFragmentHeaderParserStatus;

typedef struct _GstMssFragmentParser
{
  GstFragmentHeaderParserStatus status;
  GstTfxdBox tfxd;
  GstTfrfBox tfrf;
} GstMssFragmentParser;

void gst_mss_fragment_parser_init (GstMssFragmentParser * parser);
void gst_mss_fragment_parser_clear (GstMssFragmentParser * parser);
gboolean gst_mss_fragment_parser_add_buffer (GstMssFragmentParser * parser, GstBuffer * buf);

G_END_DECLS

#endif /* __GST_MSS_FRAGMENT_PARSER_H__ */
