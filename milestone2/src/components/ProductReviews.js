import React, { useState } from 'react';

const ProductReviews = ({ product }) => {
  const [reviews, setReviews] = useState([]); // State to store reviews
  const [newReview, setNewReview] = useState(''); // State for a new review input

  const handleAddReview = () => {
    if (newReview.trim() !== '') {
      setReviews([...reviews, newReview]);
      setNewReview('');
    }
  };

  return (
    <div>
      <ul>
        {reviews.map((review, index) => (
          <li key={index}>{review}</li>
        ))}
      </ul>
      <div>
        <textarea
          value={newReview}
          onChange={(e) => setNewReview(e.target.value)}
          placeholder="Add a review..."
        />
        <button onClick={handleAddReview}>Submit Review</button>
      </div>
    </div>
  );
};

export default ProductReviews;