import React from 'react';
import '../App.css'; // Make sure to import your CSS file

const ProductDetails = ({ product, addToCart }) => {
  const handleAddToCart = () => {
    addToCart({ ...product, quantity: 1 }); // Default quantity to 1
  };

  return (
    <div className="container">
      <div className="row">
        <div className="col-md-6 magnify-container">
          <img
            src={product.url}
            className="img-fluid magnify-image"
            alt={product.name}
          />
        </div>
        <div className="col-md-6">
          <h2>{product.name}</h2>
          <p>Category: {product.category}</p>
          <p>Seller: {product.seller}</p>
          <p>Price: Rs. {product.price}</p>
          <p>Description: {product.description}</p>
          <div className="mb-3">
            <button className="btn btn-primary" onClick={handleAddToCart}>
              Add to Cart
            </button>
          </div>
        </div>
      </div>
    </div>
  );
};

export default ProductDetails;
