template <typename Texture, typename Identifier>
void ResourceHolder<Texture, Identifier>::load(Identifier id,
  const std::string& filename)
{
  std::unique_ptr<Texture> texture(new Texture());
  if (!texture->loadFromFile(filename))
    throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
  insertResource(id, std::move(texture));
}

template <typename Texture, typename Identifier>
Texture& ResourceHolder<Texture, Identifier>::get(Identifier id)
{
  auto found = mTextureMap.find(id);
  assert(found != mTextureMap.end());
  return *found->second;
}

template <typename Texture, typename Identifier>
const Texture& ResourceHolder<Texture, Identifier>::get(Identifier id) const
{
  auto found = mTextureMap.find(id);
  assert(found != mTextureMap.end());
  return *found->second;
}

template <typename Texture, typename Identifier>
void ResourceHolder<Texture, Identifier>::insertResource(Identifier id, std::unique_ptr<Texture> texture)
{
  auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
  assert(inserted.second);
}