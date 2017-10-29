module.exports = {
    "env": {
        "node": true
    },
    "extends": ["eslint:recommended", "plugin:node/recommended"],
    "plugins": ["node"],
    "rules": {
        "indent": [
            "error",
            4
        ],
        "linebreak-style": [
            "error",
            "unix"
        ],
        "quotes": [
            "error",
            "single"
        ],
        "semi": [
            "error",
            "always"
        ]
    }
};