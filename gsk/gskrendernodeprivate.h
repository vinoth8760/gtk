#ifndef __GSK_RENDER_NODE_PRIVATE_H__
#define __GSK_RENDER_NODE_PRIVATE_H__

#include "gskrendernode.h"
#include <cairo.h>

G_BEGIN_DECLS

typedef struct _GskRenderNodeClass GskRenderNodeClass;

#define GSK_IS_RENDER_NODE_TYPE(node,type) (GSK_IS_RENDER_NODE (node) && (node)->node_class->node_type == (type))

struct _GskRenderNode
{
  const GskRenderNodeClass *node_class;
  GskRenderTree *tree;

  /* Use for debugging */
  char *name;

  /* Scaling filters */
  GskScalingFilter min_filter;
  GskScalingFilter mag_filter;

  graphene_rect_t bounds;
};

struct _GskRenderNodeClass
{
  GskRenderNodeType node_type;
  gsize struct_size;
  const char *type_name;
  void (* draw) (GskRenderNode *node,
                 cairo_t       *cr);
};

GskRenderNode *gsk_render_tree_new_node (GskRenderTree  *tree, const GskRenderNodeClass *node_class, gsize extra_size);
gpointer gsk_render_tree_allocate (GskRenderTree *self, gsize n_bytes, gsize align_size);
void gsk_render_tree_add_cleanup (GskRenderTree  *tree, GDestroyNotify notify, gpointer data);
GskRenderNode *gsk_render_tree_ref_foreign (GskRenderTree  *tree, GskRenderNode *node);

GskRenderTree *gsk_render_node_get_tree (GskRenderNode *self);
void gsk_render_node_get_bounds (GskRenderNode   *node,
                                 graphene_rect_t *frame);
double gsk_opacity_node_get_opacity (GskRenderNode *node);

const GskRoundedRect * gsk_border_node_peek_outline (GskRenderNode *node);
float gsk_border_node_get_width (GskRenderNode *node, guint i);
const GdkRGBA * gsk_border_node_peek_color (GskRenderNode *node, guint i);

cairo_surface_t *gsk_cairo_node_get_surface (GskRenderNode *node);

GskTexture *gsk_texture_node_get_texture (GskRenderNode *node);

const GdkRGBA *gsk_color_node_peek_color (GskRenderNode *node);

const graphene_rect_t * gsk_clip_node_peek_clip (GskRenderNode *node);

const GskRoundedRect * gsk_rounded_clip_node_peek_clip (GskRenderNode *node);

GskRenderNode * gsk_shadow_node_get_child (GskRenderNode *node);
const GskShadow * gsk_shadow_node_peek_shadow (GskRenderNode *node, gsize i);
gsize gsk_shadow_node_get_n_shadows (GskRenderNode *node);

void gsk_transform_node_get_transform (GskRenderNode *node, graphene_matrix_t *transform);

GskRenderNode * gsk_blend_node_get_bottom_child (GskRenderNode *node);
GskRenderNode * gsk_blend_node_get_top_child (GskRenderNode *node);
GskBlendMode gsk_blend_node_get_blend_node (GskRenderNode *node);

GskRenderNode * gsk_cross_fade_node_get_start_child (GskRenderNode *node);
GskRenderNode * gsk_cross_fade_node_get_end_child (GskRenderNode *node);
double gsk_cross_fade_node_get_progress (GskRenderNode *node);

G_END_DECLS

#endif /* __GSK_RENDER_NODE_PRIVATE_H__ */
