import React from 'react';
import '../App.css'; 
import ProductReviews from './ProductReviews';

const ProductDetails = ({ product, addToCart }) => {
  const handleAddToCart = () => {
    addToCart({ ...product, quantity: 1 }); // Default quantity to 1
  };

  return (
    <div className="container mt-4">
      <div className="row">
        {/* Product Image */}
        <div className="col-md-6">
          <img
            src={product.url}
            className="img-fluid product-image"
            alt={product.name}
          />

          {/* Add to Cart and Buy Now buttons with gap */}
          <div className="mt-3">
            <button className="btn btn-success btn-block" onClick={handleAddToCart}>
              <i className="fas fa-shopping-cart"></i> Add to Cart
            </button>
            <a href="/cart" className="btn btn-success btn-block mt-2">
              <i className="fas fa-shopping-bag"></i> Buy Now
            </a>
          </div>
        </div>

        {/* Product Information */}
        <div className="col-md-6">
          <h3 style={{ fontSize: '40px' }}>{product.name}</h3>
          <p style={{ fontSize: '20px' }}> <strong>Price:</strong> Rs. {product.price}</p>
          <p style={{ fontSize: '30px' }}><strong>Description:</strong> {product.description}</p>

          {/* Color Options */}
          <div className="card">
            <div className="card-body">
              <h5 className="card-title" style={{ fontSize: '20px' }}>Shades of Product Available</h5>
              <div className="row">
                <div className="col-sm-4">
                  <div className="card size-card" >
                    <div className="card-body">
                      <h6 className="card-title">Red</h6>
                    </div>
                  </div>
                </div>
                <div className="col-sm-4">
                  <div className="card size-card" >
                    <div className="card-body">
                      <h6 className="card-title">Blue</h6>
                    </div>
                  </div>
                </div>
                <div className="col-sm-4">
                  <div className="card size-card" >
                    <div className="card-body">
                      <h6 className="card-title">Black</h6>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>

          {/* Star Ratings */}
          <p className="star-rating">
            <strong>Ratings:</strong>
            <i className="fas fa-star"></i>
            <i className="fas fa-star"></i>
            <i className="fas fa-star"></i>
            <i className="far fa-star"></i>
            <i className="far fa-star"></i>
          </p>
        </div>
      </div>

      <div className="row mt-3">
        <div className="col-md-12">
          <h3>Customer Reviews</h3>
          <ProductReviews />
        </div>
      </div>
    </div>
  );
};

export default ProductDetails;
