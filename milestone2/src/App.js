import React, { useEffect, useState } from 'react';
import './App.css';
import Header from './components/Header';
import ProductList from './components/ProductList';
import CartList from './components/CartList';
import ProductDetail from './components/ProductDetail';
import UserProfileModal from './components/UserProfileModal'; // Import UserProfileModal component
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';

function App() {
  const [products, setProducts] = useState([]);
  const [cart, setCart] = useState([]);
  const [showCart, setShowCart] = useState(false);
  const [selectedProduct, setSelectedProduct] = useState(null);
  const [filteredProducts, setFilteredProducts] = useState([]);
  const [userProfile, setUserProfile] = useState({
    name: 'John Doe', // Example user data
    email: 'john.doe@example.com',

  });
  const [isUserProfileOpen, setIsUserProfileOpen] = useState(false);

  async function getProductDetails() {
    try {
      const response = await axios.get('http://localhost:3001/products');
      setProducts(response.data);
    } catch (error) {
      console.error('Error fetching data:', error);
    }
  }

  useEffect(() => {
    getProductDetails();
  }, []);

  const addToCart = (data) => {
    setCart([...cart, { ...data, quantity: 1 }]);
  };

  const handleShow = (value) => {
    setShowCart(value);
    setSelectedProduct(null);
  };

  const onSelectProduct = (product) => {
    setSelectedProduct(product);
    setShowCart(false);
  };

  const handleSearch = (query) => {
    const filtered = products.filter((product) =>
      product.name.toLowerCase().includes(query.toLowerCase())
    );
    setFilteredProducts(filtered);
  };

  const openUserProfile = () => {
    setIsUserProfileOpen(true);
  };

  const closeUserProfile = () => {
    setIsUserProfileOpen(false);
  };

  return (
    <div>
      <Header
        count={cart.length}
        handleShow={handleShow}
        handleSearch={handleSearch}
        openUserProfile={openUserProfile}
      />
      {showCart ? (
        <CartList cart={cart} />
      ) : selectedProduct ? (
        <ProductDetail product={selectedProduct} addToCart={addToCart} />
      ) : (
        <ProductList
          products={filteredProducts.length > 0 ? filteredProducts : products}
          addToCart={addToCart}
          onSelectProduct={onSelectProduct}
        />
      )}

      {isUserProfileOpen && (
        <UserProfileModal user={userProfile} onClose={closeUserProfile} />
      )}
    </div>
  );
}

export default App;
