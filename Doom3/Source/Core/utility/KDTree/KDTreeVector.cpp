#include "KDTree.h"

//This file is implementation KDTree having Vector2,3 as component type

/// <summary>
/// https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf 15page
/// </summary>
/// <param name="targetMinNodeDimension"></param>
/// <returns></returns>

template <>
typename dooms::KDTree<math::Vector<3, FLOAT32>>::node_view_type dooms::KDTree<math::Vector<3, FLOAT32>>::FindNearestNode(const typename node_type::component_type& componentValue)
{
	return {};
}

template<typename T>
typename dooms::KDTree<T>::node_view_type dooms::KDTree<T>::FindNearestNode(const typename node_type::component_type& componentValue)
{
	return node_view_type();
}

template class dooms::KDTree<math::Vector3>;