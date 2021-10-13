#include "KDTree.h"

//This file is implementation KDTree having Vector2,3 as component type

/// <summary>
/// https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf 15page
/// </summary>
/// <param name="targetMinNodeDimension"></param>
/// <returns></returns>

template <>
typename doom::KDTree<math::Vector<3, float>>::node_view_type doom::KDTree<math::Vector<3, float>>::FindNearestNode(const typename node_type::component_type& componentValue)
{
	return {};
}

template<typename T>
typename doom::KDTree<T>::node_view_type doom::KDTree<T>::FindNearestNode(const typename node_type::component_type& componentValue)
{
	return node_view_type();
}

template class doom::KDTree<math::Vector3>;