#pragma once
#include "Buffer.h"

#include <array>

#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>

#include "Mesh.reflection.h"
namespace dooms
{

	class ThreeDModelMesh;

	namespace graphics
	{
		class Graphics_Server;
		class DOOM_API D_CLASS Mesh : public Buffer
		{
			GENERATE_BODY()

		private:

			struct D_STRUCT VertexBufferLayout : public DObject
			{
				GENERATE_BODY_VertexBufferLayout()

				D_PROPERTY()
				UINT32 mStride;

				D_PROPERTY()
				UINT32 mOffset;
			};
			
		private:

			D_PROPERTY()
			const ThreeDModelMesh* mTargetThreeDModelMesh;

			/// <summary>
			/// DX11 bind this buffer
			/// </summary>
			D_PROPERTY()
			BufferID mVertexDataBuffer;

			D_PROPERTY()
			BufferID mElementBufferObjectID;	

			/// <summary>
			///	DX11 doesn't have this concept. it just bind VertexDataBuffer
			///
			/// OpenGL bind this buffer
			/// </summary>
			D_PROPERTY()
			BufferID mVertexArrayObjectID;
		
			//UINT32 mVertexBufferObject; <- Use Buffer::data

			//const ThreeDModelMesh* mThreeDModelMesh; don't save ModelMeshAssetData
			D_PROPERTY()
			UINT64 mNumOfIndices;
			D_PROPERTY()
			UINT64 mNumOfVertices;
			D_PROPERTY()
			GraphicsAPI::ePrimitiveType mPrimitiveType;

			D_PROPERTY()
			UINT32 mVertexArrayFlag;

			D_PROPERTY()
			UINT32 mTotalStride;

			D_PROPERTY()
			UINT32 mVertexBufferLayoutCount;

			D_PROPERTY()
			std::array<VertexBufferLayout, 10> mVertexBufferLayouts;

			static UINT64 BOUND_VERTEX_ARRAY_ID; // only used for OPENGL
			inline static const UINT32 MAX_VERTEX_BUFFER_LAYOUT_COUNT = 32;
			static UINT64 BOUND_VERTEX_BUFFER_ID[MAX_VERTEX_BUFFER_LAYOUT_COUNT]; // for OPENGL, Only first element is used
			static UINT64 BOUND_INDEX_BUFFER_ID; // INDEX ( ELEMENT BUFFER )

			/*
			/// <summary>
			/// bind buffer array object
			/// </summary>
			/// <returns></returns>
			D_FUNCTION()
			FORCE_INLINE void BindBuffer() const noexcept final
			{
				D_ASSERT(mVertexArrayObjectID.IsValid());

				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(VERTEX_ARRAY_TAG, mVertexArrayObjectID))
				{
					GraphicsAPI::BindVertexArrayObject(mVertexArrayObjectID);
				}
			}

			D_FUNCTION()
			FORCE_INLINE void BindElementBuffer() const noexcept
			{
				D_ASSERT(mElementBufferObjectID.IsValid());

				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(INDEX_BUFFER_TAG, mElementBufferObjectID))
				{
					GraphicsAPI::BindIndexBufferObject(mElementBufferObjectID);
				}
			}
			*/

			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			D_PROPERTY()
			physics::AABB3D mAABB3D{math::Vector4{-1.0f}, math::Vector4{1.0f}};
			D_PROPERTY()
			physics::Sphere mSphere{math::Vector3{0.0f}, 1.0f};

			void OnSetPendingKill() override;

			FORCE_INLINE void BindVertexArrayObject() const
			{
				if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
				{
					D_ASSERT(mVertexArrayObjectID.IsValid() == true);
					if (BOUND_VERTEX_ARRAY_ID != mVertexArrayObjectID.GetBufferID())
					{
						BOUND_VERTEX_ARRAY_ID = mVertexArrayObjectID;
						dooms::graphics::GraphicsAPI::BindVertexArrayObject(mVertexArrayObjectID);
					}
				}
			}
			FORCE_INLINE void BindVertexBufferObject() const
			{
				D_ASSERT(mVertexDataBuffer.IsValid() == true);
				D_ASSERT(mTotalStride > 0);

				if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
				{
					if (BOUND_VERTEX_BUFFER_ID[0] != mVertexArrayObjectID.GetBufferID())
					{
						BOUND_VERTEX_BUFFER_ID[0] = mVertexArrayObjectID;
						dooms::graphics::GraphicsAPI::BindVertexDataBuffer
						(
							mVertexDataBuffer,
							0,
							mTotalStride,
							0
						);
					}
				}
				else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
				{
					for (UINT32 bufferLayoutIndex = 0; bufferLayoutIndex < mVertexBufferLayoutCount; bufferLayoutIndex++)
					{
						if (BOUND_VERTEX_BUFFER_ID[bufferLayoutIndex] != mVertexDataBuffer.GetBufferID())
						{
							BOUND_VERTEX_BUFFER_ID[bufferLayoutIndex] = mVertexDataBuffer;
							dooms::graphics::GraphicsAPI::BindVertexDataBuffer
							(
								mVertexDataBuffer,
								bufferLayoutIndex,
								mVertexBufferLayouts[bufferLayoutIndex].mStride,
								mVertexBufferLayouts[bufferLayoutIndex].mOffset
							);
						}
					}

				}
				else
				{
					NEVER_HAPPEN;
				}

			}
			FORCE_INLINE void BindIndexBufferObject() const
			{
				D_ASSERT(mVertexDataBuffer.IsValid() == true);
				if (BOUND_INDEX_BUFFER_ID != mElementBufferObjectID.GetBufferID())
				{
					BOUND_INDEX_BUFFER_ID = mElementBufferObjectID;
					dooms::graphics::GraphicsAPI::BindBuffer(mElementBufferObjectID, 0, graphics::GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
				}
			}
			FORCE_INLINE void BindVertexBufferObject
			(
				const UINT32 bindingPosition,
				const UINT32 stride,
				const UINT32 offset
			) const
			{
				D_ASSERT(mVertexDataBuffer.IsValid() == true);
				if (BOUND_VERTEX_BUFFER_ID[bindingPosition] != mVertexDataBuffer.GetBufferID())
				{
					BOUND_VERTEX_BUFFER_ID[bindingPosition] = mVertexDataBuffer;
					dooms::graphics::GraphicsAPI::BindVertexDataBuffer
					(
						mVertexDataBuffer,
						bindingPosition,
						stride,
						offset
					);
				}
			}

			void CreateVertexArrayObjectIfNotExist();

	
		public:

			

			Mesh();
			virtual ~Mesh();
			
			Mesh
			(
				const long long int dataCount, 
				const void* data, 
				GraphicsAPI::ePrimitiveType primitiveType,
				UINT32 vertexArrayFlag,
				const bool dynamicWrite
			);
			Mesh(const ThreeDModelMesh& threeDModelMesh);
			Mesh& operator=(const ThreeDModelMesh& threeDModelMesh);

			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;

			Mesh(Mesh&&) noexcept = default;
			Mesh& operator=(Mesh&&) noexcept = default;

			const ThreeDModelMesh* GetTargetThreeDModelMesh() const;
			void DeleteBuffers() final;

			
			void CreateBufferObject
			(
				const long long int dataComponentCount, 
				const void* data, 
				GraphicsAPI::ePrimitiveType primitiveType,
				UINT32 vertexArrayFlag,
				const bool dynamicWrite
			) noexcept;
			void CreateBufferObjectFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept;

			/* You can't update buffer partially in D3D11. Use map, unmap function.
			void UpdateVertexData(const long long int dataSize, const void* data, const long long int offsetInByte) const noexcept;
			*/


			FORCE_INLINE void Draw() const
			{
				D_ASSERT(mPrimitiveType != GraphicsAPI::ePrimitiveType::NONE);

				if(graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
				{
					BindVertexArrayObject();
				}
				else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
				{
					BindVertexBufferObject();
				}
				else
				{
					NEVER_HAPPEN;
				}

				if (IsElementBufferGenerated() == true)
				{// TODO : WHY THIS MAKE ERROR ON RADEON GPU, CHECK THIS https://stackoverflow.com/questions/18299646/gldrawelements-emits-gl-invalid-operation-when-using-amd-driver-on-linux
					// you don't need bind EBO everytime, EBO will be bound automatically when bind VAO
					BindIndexBufferObject();
					GraphicsAPI::DrawIndexed(mPrimitiveType, mNumOfIndices);
				}
				else
				{
					GraphicsAPI::Draw(mPrimitiveType, 0, mNumOfVertices);
				}
			}
			FORCE_INLINE void DrawArray(const INT32 startVertexLocation, const UINT32 vertexCount) const
			{
				D_ASSERT(mPrimitiveType != GraphicsAPI::ePrimitiveType::NONE);

				if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
				{
					BindVertexArrayObject();
				}
				else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
				{
					BindVertexBufferObject();
				}
				else
				{
					NEVER_HAPPEN;
				}

				GraphicsAPI::Draw(mPrimitiveType, vertexCount, startVertexLocation);
			}

			FORCE_INLINE void DrawArray(const GraphicsAPI::ePrimitiveType primitiveType, const INT32 startVertexLocation, const INT32 vertexCount) const
			{
				D_ASSERT(primitiveType != GraphicsAPI::ePrimitiveType::NONE);

				if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
				{
					BindVertexArrayObject();
				}
				else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
				{
					BindVertexBufferObject();
				}
				else
				{
					NEVER_HAPPEN;
				}

				GraphicsAPI::Draw(primitiveType, vertexCount, startVertexLocation);
			}

			static constexpr UINT32 GetStride(const UINT32 vertexArrayFlag);

			

			D_FUNCTION()
			virtual bool IsBufferGenerated() const final;

			D_FUNCTION()
			FORCE_INLINE bool IsElementBufferGenerated() const 
			{
				return mElementBufferObjectID.IsValid();
			}

			/*
			D_FUNCTION()
			void UpdateElementBuffer(const UINT32* indices, const UINT32 indiceCount);
			*/


			D_FUNCTION()
			const physics::AABB3D& GetBoundingBox() const;
			D_FUNCTION()
			const physics::Sphere& GetBoundingSphere() const;

			D_FUNCTION()
			const BufferID& GetVertexArrayObjectID() const;
			D_FUNCTION()
			const BufferID& GetElementBufferObjectID() const;

			/**
			 * \brief You should unmap mapped buffer object before use it 
			 * \param mapBufferAccessOption 
			 * \return 
			 */
			void* MapVertexDataBuffer(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapVertexDataBuffer();
			void* MapElementBuffer(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapElementBuffer();
		};
	}
}