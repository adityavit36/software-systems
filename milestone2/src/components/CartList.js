import { useEffect, useState } from 'react';
import '../App.css';

function CartList({ cart }) {
    const [CART, setCART] = useState([]);

    useEffect(() => {
        setCART(cart);
    }, [cart]);

    return (
        <div className="CartList container">
            {CART?.map((cartItem, cartindex) => (
                <div key={cartindex} className="CartItem row mb-3 align-items-center">
                    <div className="col-md-2">
                        <img src={cartItem.url} width={40} alt={cartItem.name} className="img-fluid" />
                    </div>
                    <div className="col-md-4">
                        <span>{cartItem.name}</span>
                    </div>
                    <div className="col-md-4 QuantityButtons">
                        <button
                            className="btn btn-secondary"
                            onClick={() => {
                                const _CART = CART.map((item, index) => (cartindex === index ? { ...item, quantity: item.quantity > 0 ? item.quantity - 1 : 0 } : item));
                                setCART(_CART);
                            }}
                        >
                            -
                        </button>
                        <span className="mx-2">{cartItem.quantity}</span>
                        <button
                            className="btn btn-secondary"
                            onClick={() => {
                                const _CART = CART.map((item, index) => (cartindex === index ? { ...item, quantity: item.quantity + 1 } : item));
                                setCART(_CART);
                            }}
                        >
                            +
                        </button>
                    </div>
                    <div className="col-md-2 TotalPrice">
                        <span>Rs. {cartItem.price * cartItem.quantity}</span>
                    </div>
                </div>
            ))}

            <p className="CartTotal font-weight-bold">
                Total: Rs.
                {CART.map(item => item.price * item.quantity).reduce((total, value) => total + value, 0)}
            </p>
        </div>
    );
}

export default CartList;
