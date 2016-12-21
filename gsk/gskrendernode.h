/* GSK - The GTK Scene Kit
 *
 * Copyright 2016  Endless
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GSK_RENDER_NODE_H__
#define __GSK_RENDER_NODE_H__

#if !defined (__GSK_H_INSIDE__) && !defined (GSK_COMPILATION)
#error "Only <gsk/gsk.h> can be included directly."
#endif

#include <gsk/gskroundedrect.h>
#include <gsk/gsktypes.h>

G_BEGIN_DECLS

#define GSK_TYPE_RENDER_TREE (gsk_render_tree_get_type ())

GDK_AVAILABLE_IN_3_90
G_DECLARE_FINAL_TYPE (GskRenderTree, gsk_render_tree, GSK, RENDER_TREE, GObject)

#define GSK_TYPE_RENDER_NODE (gsk_render_node_get_type ())
#define GSK_IS_RENDER_NODE(obj) ((obj) != NULL)

typedef struct _GskRenderTree           GskRenderTree;
typedef struct _GskRenderNode           GskRenderNode;
typedef struct _GskColorStop            GskColorStop;
typedef struct _GskShadow               GskShadow;

struct _GskColorStop
{
  double offset;
  GdkRGBA color;
};

struct _GskShadow
{
  GdkRGBA color;
  float dx;
  float dy;
  float spread;
  float radius;
};

GDK_AVAILABLE_IN_3_90
GskRenderTree * gsk_render_tree_new (void);

GDK_AVAILABLE_IN_3_90
GType gsk_render_node_get_type (void) G_GNUC_CONST;

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_render_node_ref                     (GskRenderNode *node);
GDK_AVAILABLE_IN_3_90
void                    gsk_render_node_unref                   (GskRenderNode *node);

GDK_AVAILABLE_IN_3_90
GskRenderNodeType       gsk_render_node_get_node_type           (GskRenderNode *node);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_color_node_new                      (GskRenderTree            *tree,
                                                                 const GdkRGBA            *rgba,
                                                                 const graphene_rect_t    *bounds);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_texture_node_new                    (GskRenderTree            *tree,
                                                                 GskTexture               *texture,
                                                                 const graphene_rect_t    *bounds);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_linear_gradient_node_new            (GskRenderTree            *tree,
                                                                 const graphene_rect_t    *bounds,
                                                                 const graphene_point_t   *start,
                                                                 const graphene_point_t   *end,
                                                                 const GskColorStop       *color_stops,
                                                                 gsize                     n_color_stops);
GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_repeating_linear_gradient_node_new  (GskRenderTree            *tree,
                                                                 const graphene_rect_t    *bounds,
                                                                 const graphene_point_t   *start,
                                                                 const graphene_point_t   *end,
                                                                 const GskColorStop       *color_stops,
                                                                 gsize                     n_color_stops);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_border_node_new                     (GskRenderTree            *tree,
                                                                 const GskRoundedRect     *outline,
                                                                 const float               border_width[4],
                                                                 const GdkRGBA             border_color[4]);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_inset_shadow_node_new               (GskRenderTree            *tree,
                                                                 const GskRoundedRect     *outline,
                                                                 const GdkRGBA            *color,
                                                                 float                     dx,
                                                                 float                     dy,
                                                                 float                     spread,
                                                                 float                     blur_radius);
GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_outset_shadow_node_new              (GskRenderTree            *tree,
                                                                 const GskRoundedRect     *outline,
                                                                 const GdkRGBA            *color,
                                                                 float                     dx,
                                                                 float                     dy,
                                                                 float                     spread,
                                                                 float                     blur_radius);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_cairo_node_new                      (GskRenderTree            *tree,
                                                                 const graphene_rect_t    *bounds);
GDK_AVAILABLE_IN_3_90
cairo_t *               gsk_cairo_node_get_draw_context         (GskRenderNode            *node,
                                                                 GskRenderer              *renderer);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_container_node_new                  (GskRenderTree            *tree,
                                                                 GskRenderNode           **children,
                                                                 guint                     n_children);
GDK_AVAILABLE_IN_3_90
guint                   gsk_container_node_get_n_children       (GskRenderNode            *node);
GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_container_node_get_child            (GskRenderNode            *node,
                                                                 guint                     idx);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_transform_node_new                  (GskRenderTree            *tree,
                                                                 GskRenderNode            *child,
                                                                 const graphene_matrix_t  *transform);
GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_transform_node_get_child            (GskRenderNode            *node);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_opacity_node_new                    (GskRenderTree            *tree,
                                                                 GskRenderNode            *child,
                                                                 double                    opacity);
GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_opacity_node_get_child              (GskRenderNode            *node);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_clip_node_new                       (GskRenderTree            *tree,
                                                                 GskRenderNode            *child,
                                                                 const graphene_rect_t    *clip);
GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_clip_node_get_child                 (GskRenderNode            *node);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_rounded_clip_node_new               (GskRenderTree            *tree,
                                                                 GskRenderNode            *child,
                                                                 const GskRoundedRect     *clip);
GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_rounded_clip_node_get_child         (GskRenderNode            *node);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_shadow_node_new                     (GskRenderTree            *tree,
                                                                 GskRenderNode            *child,
                                                                 const GskShadow          *shadows,
                                                                 gsize                     n_shadows);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_blend_node_new                      (GskRenderTree            *tree,
                                                                 GskRenderNode            *bottom,
                                                                 GskRenderNode            *top,
                                                                 GskBlendMode              blend_mode);

GDK_AVAILABLE_IN_3_90
GskRenderNode *         gsk_cross_fade_node_new                 (GskRenderTree            *tree,
                                                                 GskRenderNode            *start,
                                                                 GskRenderNode            *end,
                                                                 double                    progress);

GDK_AVAILABLE_IN_3_90
void                    gsk_render_node_set_scaling_filter      (GskRenderNode *node,
                                                                 GskScalingFilter min_filter,
                                                                 GskScalingFilter mag_filter);

GDK_AVAILABLE_IN_3_90
void                    gsk_render_node_set_name                (GskRenderNode *node,
                                                                 const char    *name);
GDK_AVAILABLE_IN_3_90
const char *            gsk_render_node_get_name                (GskRenderNode *node);

GDK_AVAILABLE_IN_3_90
void                    gsk_render_node_draw                    (GskRenderNode *node,
                                                                 cairo_t       *cr);
G_END_DECLS

#endif /* __GSK_RENDER_NODE_H__ */
