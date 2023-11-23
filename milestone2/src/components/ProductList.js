import React from 'react';

function ProductList({ products, addToCart, onSelectProduct }) {
  return (
    <div className='flex'>
      {products.map((product, productIndex) => (
        <div key={productIndex} style={{ width: '33%' }}>
          <div className='product-item'>
            <img src={product.url} alt={product.name} width="100%" />
            <p>{product.name} | {product.category} </p>
            <p>{product.seller}</p>
            <p>Rs. {product.price} /-</p>
            <button
              onClick={() => addToCart(product)}
              className="btn btn-success" // Add Bootstrap classes
              style={{ marginRight: '8px' }} // Add inline styles
            >
             <i className="fas fa-shopping-cart"></i> Add To Cart
            </button>
            <button
              onClick={() => onSelectProduct(product)}
              className="btn btn-primary" // Add Bootstrap classes
            >
           <i className="fas fa-shopping-bag"></i>   View Details
            </button>
          </div>
        </div>
      ))}
    </div>
  );
}

export default ProductList;
