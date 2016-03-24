package us.hiku.sdk.sample;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.widget.TextView;

import us.hiku.android.sdk.HikuSetupSDK;


public class UserActivity extends AppCompatActivity {

    HikuSetupSDK mSdk;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user_token);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        mSdk = HikuSetupSDK.getInstance(this);

        TextView email = (TextView) findViewById(R.id.email);
        email.setText(mSdk.getEmail());

        TextView token = (TextView) findViewById(R.id.token);
        token.setText(mSdk.getAuthorizationToken());

    }

    @Override
    public boolean onSupportNavigateUp() {
        onBackPressed();
        return true;
    }
}
